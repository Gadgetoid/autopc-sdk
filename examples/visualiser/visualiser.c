/* Spectrum visualiser: while the built-in CD Player plays, reads the audio
   ring the CD driver fills in the faceplate's memory and draws 32 bars with
   peaks on the faceplate. It only reads; Esc exits and releases the keys. */
#include "autopc.h"
#include "autopc_app.h"

#define FACEPLATE_VENDOR   0x1398
#define FACEPLATE_DEVICE   0x0003
#define BAR0_OFFSET        0
#define BAR1_OFFSET        4
#define REGISTERS_OFFSET   0x2000
#define REGISTERS_SIZE     0x40
#define LONG_WINDOW        0x800
#define CD_RING_START      0x30
#define CD_RING_LAST       0x34
#define MEMORY_SIZE        0x10000
#define OFFSET_MASK        0xFFFF

#define FFT_BITS           8
#define FFT_SIZE           (1 << FFT_BITS)
#define BARS               32
#define BAR_WIDTH          8
#define SCREEN_WIDTH       256
#define SCREEN_HEIGHT      64
#define YELLOW_FROM        36
#define RED_FROM           52
#define FRAME_MS           66
#define PEAK_HOLD_FRAMES   12
#define STALE_FRAMES       4
#define PIXELS_PER_OCTAVE  6
#define FLOOR_OCTAVES      4

#define KEYPAD_REGISTER    0x1001
#define KEY_DOWN_MESSAGE   0xBD00
#define VK_ESCAPE_KEY      0x1B
#define PM_REMOVE_FLAG     1

typedef struct {
    DWORD config_offset, offset, size, type;
} pci_window_t;

typedef BOOL (*GetPCIDevAddresses_t)(DWORD, DWORD, DWORD, const pci_window_t *, DWORD *);
typedef HDC (WINAPI *CreateDCW_t)(const WCHAR *, const WCHAR *, const WCHAR *, const void *);
typedef BOOL (WINAPI *DeleteDC_t)(HDC);
typedef int (WINAPI *FillRect_t)(HDC, const RECT *, HBRUSH);
typedef HBRUSH (WINAPI *CreateSolidBrush_t)(COLORREF);
typedef BOOL (WINAPI *DeleteObject_t)(HGDIOBJ);
typedef ATOM (WINAPI *RegisterClassW_t)(const WNDCLASSW *);
typedef HWND (WINAPI *CreateWindowExW_t)(DWORD, const WCHAR *, const WCHAR *, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, void *);
typedef BOOL (WINAPI *DestroyWindow_t)(HWND);
typedef BOOL (WINAPI *PeekMessageW_t)(MSG *, HWND, UINT, UINT, UINT);
typedef LRESULT (WINAPI *DispatchMessageW_t)(const MSG *);
typedef LRESULT (WINAPI *DefWindowProcW_t)(HWND, UINT, WPARAM, LPARAM);
typedef HANDLE (WINAPI *CreateFileW_t)(const WCHAR *, DWORD, DWORD, void *, DWORD, DWORD, HANDLE);
typedef BOOL (WINAPI *DeviceIoControl_t)(HANDLE, DWORD, void *, DWORD, void *, DWORD, DWORD *, void *);
typedef DWORD (WINAPI *GetTickCount_t)(void);

static CreateDCW_t p_create_dc;
static DeleteDC_t p_delete_dc;
static FillRect_t p_fill_rect;
static CreateSolidBrush_t p_create_solid_brush;
static DeleteObject_t p_delete_object;
static RegisterClassW_t p_register_class;
static CreateWindowExW_t p_create_window;
static DestroyWindow_t p_destroy_window;
static PeekMessageW_t p_peek_message;
static DispatchMessageW_t p_dispatch_message;
static DefWindowProcW_t p_def_window_proc;
static CreateFileW_t p_create_file;
static DeviceIoControl_t p_device_io_control;
static GetTickCount_t p_get_tick_count;

static volatile DWORD *registers;
static volatile unsigned char *faceplate_memory;
static short twiddle_cos[FFT_SIZE / 2], twiddle_sin[FFT_SIZE / 2];
static int real_part[FFT_SIZE], imaginary_part[FFT_SIZE];
static int levels[BARS], peaks[BARS], peak_hold[BARS];
static const unsigned char bar_bins[BARS + 1] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 24, 28, 33, 38, 44, 51, 60, 69, 81, 94, 109, 127,
};
static BOOL quit;

static BOOL bind_functions(void) {
    HINSTANCE coredll = LoadLibraryW(L"coredll.dll");
    p_create_dc = (CreateDCW_t)GetProcAddressW(coredll, L"CreateDCW");
    p_delete_dc = (DeleteDC_t)GetProcAddressW(coredll, L"DeleteDC");
    p_fill_rect = (FillRect_t)GetProcAddressW(coredll, L"FillRect");
    p_create_solid_brush = (CreateSolidBrush_t)GetProcAddressW(coredll, L"CreateSolidBrush");
    p_delete_object = (DeleteObject_t)GetProcAddressW(coredll, L"DeleteObject");
    p_register_class = (RegisterClassW_t)GetProcAddressW(coredll, L"RegisterClassW");
    p_create_window = (CreateWindowExW_t)GetProcAddressW(coredll, L"CreateWindowExW");
    p_destroy_window = (DestroyWindow_t)GetProcAddressW(coredll, L"DestroyWindow");
    p_peek_message = (PeekMessageW_t)GetProcAddressW(coredll, L"PeekMessageW");
    p_dispatch_message = (DispatchMessageW_t)GetProcAddressW(coredll, L"DispatchMessageW");
    p_def_window_proc = (DefWindowProcW_t)GetProcAddressW(coredll, L"DefWindowProcW");
    p_create_file = (CreateFileW_t)GetProcAddressW(coredll, L"CreateFileW");
    p_device_io_control = (DeviceIoControl_t)GetProcAddressW(coredll, L"DeviceIoControl");
    p_get_tick_count = (GetTickCount_t)GetProcAddressW(coredll, L"GetTickCount");
    return p_create_dc && p_delete_dc && p_fill_rect && p_create_solid_brush && p_delete_object && p_peek_message &&
           p_dispatch_message && p_get_tick_count;
}

static BOOL map_faceplate(void) {
    static const pci_window_t windows[2] = {
        { BAR0_OFFSET, REGISTERS_OFFSET, REGISTERS_SIZE, 0 },
        { BAR1_OFFSET, 0, MEMORY_SIZE, 0 },
    };
    DWORD addresses[2] = { 0, 0 };
    HINSTANCE pci = LoadLibraryW(L"pci.dll");
    GetPCIDevAddresses_t get_addresses = pci ? (GetPCIDevAddresses_t)GetProcAddressW(pci, L"GetPCIDevAddresses") : 0;
    if (!get_addresses || !get_addresses(FACEPLATE_VENDOR, FACEPLATE_DEVICE, 2, windows, addresses)) return FALSE;
    registers = (volatile DWORD *)(addresses[0] + LONG_WINDOW);
    faceplate_memory = (volatile unsigned char *)addresses[1];
    return addresses[0] && addresses[1];
}

static void build_tables(void) {
    long long cosine = 1LL << 30, sine = 0;
    const long long step_cos = 1073418433LL, step_sin = 26350943LL;
    int i;
    for (i = 0; i < FFT_SIZE / 2; i++) {
        long long next_cos, next_sin;
        twiddle_cos[i] = (short)(cosine >> 15 > 32767 ? 32767 : cosine >> 15);
        twiddle_sin[i] = (short)(sine >> 15 > 32767 ? 32767 : sine >> 15);
        next_cos = (cosine * step_cos - sine * step_sin) >> 30;
        next_sin = (sine * step_cos + cosine * step_sin) >> 30;
        cosine = next_cos;
        sine = next_sin;
    }
}

static int hann(int i) {
    int k = i < FFT_SIZE / 2 ? i : FFT_SIZE - i;
    int cosine = k == FFT_SIZE / 2 ? -32768 : twiddle_cos[k];
    return (32767 - cosine) >> 1;
}

static unsigned reverse_bits(unsigned value) {
    unsigned result = 0;
    int i;
    for (i = 0; i < FFT_BITS; i++) {
        result = result << 1 | (value & 1);
        value >>= 1;
    }
    return result;
}

static void transform(void) {
    int size, i, j;
    for (i = 0; i < FFT_SIZE; i++) {
        j = (int)reverse_bits((unsigned)i);
        if (j > i) {
            int swap = real_part[i];
            real_part[i] = real_part[j];
            real_part[j] = swap;
        }
        imaginary_part[i] = 0;
    }
    for (size = 2; size <= FFT_SIZE; size <<= 1) {
        int half = size >> 1, stride = FFT_SIZE / size;
        for (i = 0; i < FFT_SIZE; i += size) {
            for (j = 0; j < half; j++) {
                int c = twiddle_cos[j * stride], s = twiddle_sin[j * stride];
                int a = i + j, b = a + half;
                int tr = (real_part[b] * c + imaginary_part[b] * s) >> 15;
                int ti = (imaginary_part[b] * c - real_part[b] * s) >> 15;
                real_part[b] = (real_part[a] - tr) >> 1;
                imaginary_part[b] = (imaginary_part[a] - ti) >> 1;
                real_part[a] = (real_part[a] + tr) >> 1;
                imaginary_part[a] = (imaginary_part[a] + ti) >> 1;
            }
        }
    }
}

static int magnitude(int bin) {
    int re = real_part[bin] < 0 ? -real_part[bin] : real_part[bin];
    int im = imaginary_part[bin] < 0 ? -imaginary_part[bin] : imaginary_part[bin];
    return re > im ? re + im / 2 : im + re / 2;
}

static int bar_height(int value) {
    int height = -FLOOR_OCTAVES * PIXELS_PER_OCTAVE;
    while (value > 1) {
        value >>= 1;
        height += PIXELS_PER_OCTAVE;
    }
    return height < 0 ? 0 : height > SCREEN_HEIGHT ? SCREEN_HEIGHT : height;
}

static BOOL read_samples(void) {
    static DWORD last_sum;
    static int stale;
    DWORD start, length, sum = 0;
    int i;
    if (!registers || !faceplate_memory) return FALSE;
    start = registers[CD_RING_START / 4] & OFFSET_MASK;
    length = (registers[CD_RING_LAST / 4] & OFFSET_MASK) + 4;
    if (length < FFT_SIZE * 4 || start + length > MEMORY_SIZE) return FALSE;
    for (i = 0; i < FFT_SIZE; i++) {
        volatile unsigned char *frame = faceplate_memory + start + (DWORD)i * 4;
        int left = (short)(frame[0] | frame[1] << 8), right = (short)(frame[2] | frame[3] << 8);
        real_part[i] = ((left + right) / 2) * hann(i) >> 15;
        sum = sum * 31 + (DWORD)(left ^ right << 16);
    }
    stale = sum == last_sum ? stale + 1 : 0;
    last_sum = sum;
    return stale < STALE_FRAMES;
}

static void update_levels(BOOL playing) {
    int bar;
    if (playing) transform();
    for (bar = 0; bar < BARS; bar++) {
        int bin, loudest = 0, height;
        if (playing) {
            for (bin = bar_bins[bar]; bin < bar_bins[bar + 1] || bin == bar_bins[bar]; bin++) {
                int value = magnitude(bin);
                if (value > loudest) loudest = value;
            }
        }
        height = bar_height(loudest);
        levels[bar] = height > levels[bar] ? height : levels[bar] > 3 ? levels[bar] - 3 : 0;
        if (levels[bar] >= peaks[bar]) {
            peaks[bar] = levels[bar];
            peak_hold[bar] = PEAK_HOLD_FRAMES;
        } else if (peak_hold[bar]) {
            peak_hold[bar]--;
        } else if (peaks[bar]) {
            peaks[bar]--;
        }
    }
}

static void fill(HDC dc, int left, int top, int right, int bottom, HBRUSH brush) {
    RECT area;
    if (top >= bottom) return;
    area.left = left;
    area.top = top;
    area.right = right;
    area.bottom = bottom;
    p_fill_rect(dc, &area, brush);
}

static void draw(HBRUSH black, HBRUSH green, HBRUSH yellow, HBRUSH red, HBRUSH white) {
    HDC dc = p_create_dc(L"FACEPLT", 0, 0, 0);
    int bar;
    if (!dc) return;
    for (bar = 0; bar < BARS; bar++) {
        int left = bar * BAR_WIDTH, right = left + BAR_WIDTH - 1;
        int top = SCREEN_HEIGHT - levels[bar];
        int peak = SCREEN_HEIGHT - peaks[bar];
        fill(dc, left, 0, right + 1, top, black);
        fill(dc, right, top, right + 1, SCREEN_HEIGHT, black);
        fill(dc, left, top > SCREEN_HEIGHT - YELLOW_FROM ? top : SCREEN_HEIGHT - YELLOW_FROM, right, SCREEN_HEIGHT, green);
        fill(dc, left, top > SCREEN_HEIGHT - RED_FROM ? top : SCREEN_HEIGHT - RED_FROM, right, SCREEN_HEIGHT - YELLOW_FROM, yellow);
        fill(dc, left, top, right, SCREEN_HEIGHT - RED_FROM, red);
        if (peaks[bar] > 1) fill(dc, left, peak, right, peak + 2 > SCREEN_HEIGHT ? SCREEN_HEIGHT : peak + 2, white);
    }
    p_delete_dc(dc);
}

static LRESULT WINAPI window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    if (message == KEY_DOWN_MESSAGE && wparam == VK_ESCAPE_KEY) {
        quit = TRUE;
        return 0;
    }
    return p_def_window_proc ? p_def_window_proc(window, message, wparam, lparam) : 0;
}

static HANDLE take_keys(HINSTANCE instance, HWND *window) {
    WNDCLASSW window_class;
    HANDLE keypad;
    DWORD returned;
    *window = 0;
    if (!p_register_class || !p_create_window || !p_create_file || !p_device_io_control) return INVALID_HANDLE_VALUE;
    ZeroMemory(&window_class, sizeof window_class);
    window_class.lpfnWndProc = window_proc;
    window_class.hInstance = instance;
    window_class.lpszClassName = L"Visualiser";
    p_register_class(&window_class);
    *window = p_create_window(0, L"Visualiser", L"Visualiser", 0, 0, 0, 0, 0, 0, 0, instance, 0);
    if (!*window) return INVALID_HANDLE_VALUE;
    keypad = p_create_file(L"KPD1:", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    if (keypad != INVALID_HANDLE_VALUE) p_device_io_control(keypad, KEYPAD_REGISTER, window, sizeof *window, 0, 0, &returned, 0);
    return keypad;
}

static void release_keys(HANDLE keypad, HWND window) {
    DWORD returned;
    if (keypad != INVALID_HANDLE_VALUE) {
        p_device_io_control(keypad, KEYPAD_REGISTER, 0, 0, 0, 0, &returned, 0);
        CloseHandle(keypad);
    }
    if (window && p_destroy_window) p_destroy_window(window);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    BOOL registered = autopc_register_app(instance);
    HBRUSH black, green, yellow, red, white;
    HANDLE keypad;
    HWND window;
    MSG message;
    if (!registered && autopc_detach(instance, command_line)) return 0;
    if (!bind_functions()) return 1;
    build_tables();
    if (!map_faceplate()) {
        autopc_init();
        autopc_print(L"No faceplate found");
        Sleep(3000);
        autopc_unregister_app();
        return 1;
    }
    black = p_create_solid_brush(RGB(0, 0, 0));
    green = p_create_solid_brush(RGB(0, 255, 0));
    yellow = p_create_solid_brush(RGB(255, 255, 0));
    red = p_create_solid_brush(RGB(255, 0, 0));
    white = p_create_solid_brush(RGB(255, 255, 255));
    keypad = take_keys(instance, &window);
    while (!quit) {
        DWORD started = p_get_tick_count(), spent;
        while (p_peek_message(&message, 0, 0, 0, PM_REMOVE_FLAG)) p_dispatch_message(&message);
        update_levels(read_samples());
        draw(black, green, yellow, red, white);
        spent = p_get_tick_count() - started;
        if (spent < FRAME_MS) Sleep(FRAME_MS - spent);
    }
    release_keys(keypad, window);
    p_delete_object(black);
    p_delete_object(green);
    p_delete_object(yellow);
    p_delete_object(red);
    p_delete_object(white);
    autopc_unregister_app();
    return 0;
}
