/* Spectrum visualiser: while the built-in CD Player plays, reads the audio
   ring the CD driver fills in the faceplate's memory and draws 32 bars with
   peaks on the faceplate. It only reads; Esc exits. */
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

typedef struct {
    DWORD config_offset, offset, size, type;
} pci_window_t;

typedef BOOL (*GetPCIDevAddresses_t)(DWORD, DWORD, DWORD, const pci_window_t *, DWORD *);
typedef DWORD (WINAPI *GetTickCount_t)(void);

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

static void draw(HDC dc) {
    int bar;
    for (bar = 0; bar < BARS; bar++) {
        int left = bar * BAR_WIDTH, right = left + BAR_WIDTH - 1;
        int top = SCREEN_HEIGHT - levels[bar];
        int peak = SCREEN_HEIGHT - peaks[bar];
        autopc_fill(dc, left, 0, right + 1, top, RGB(0, 0, 0));
        autopc_fill(dc, right, top, right + 1, SCREEN_HEIGHT, RGB(0, 0, 0));
        autopc_fill(dc, left, top > SCREEN_HEIGHT - YELLOW_FROM ? top : SCREEN_HEIGHT - YELLOW_FROM, right, SCREEN_HEIGHT, RGB(0, 255, 0));
        autopc_fill(dc, left, top > SCREEN_HEIGHT - RED_FROM ? top : SCREEN_HEIGHT - RED_FROM, right, SCREEN_HEIGHT - YELLOW_FROM, RGB(255, 255, 0));
        autopc_fill(dc, left, top, right, SCREEN_HEIGHT - RED_FROM, RGB(255, 0, 0));
        if (peaks[bar] > 1) autopc_fill(dc, left, peak, right, peak + 2 > SCREEN_HEIGHT ? SCREEN_HEIGHT : peak + 2, RGB(255, 255, 255));
    }
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    BOOL mapped;
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    p_get_tick_count = (GetTickCount_t)GetProcAddressW(LoadLibraryW(L"coredll.dll"), L"GetTickCount");
    build_tables();
    mapped = map_faceplate();
    while (autopc_app_running()) {
        DWORD started = p_get_tick_count ? p_get_tick_count() : 0, spent;
        HDC dc = autopc_app_begin_draw();
        if (mapped) {
            update_levels(read_samples());
            draw(dc);
        } else {
            autopc_print(dc, L"No faceplate found");
        }
        autopc_app_end_draw(dc);
        spent = p_get_tick_count ? p_get_tick_count() - started : 0;
        if (spent < FRAME_MS) Sleep(FRAME_MS - spent);
    }
    autopc_app_stop();
    return 0;
}
