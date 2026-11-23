#include "autopc.h"
#include "autopc_app.h"
#include <mmsystem.h>

#define DRIVER_NAME        L"ddi_ct.dll"
#define DRIVER_PATH        L"\\Windows\\ddi_ct.dll"
#define DRIVER_SOURCE      L"\\Storage Card\\ddi_ct.dll"
#define DISPLAY_KEY        L"Drivers\\Display\\Intel"
#define MUSIC_PATH         L"\\Storage Card\\MUSIC.WAV"
#define PANEL_NUMBER       5
#define SCREEN_HZ          60

#define WIDTH              320
#define HEIGHT             234
#define COLOURS            256
#define DAC_WRITE_INDEX    0x3C8
#define DAC_DATA           0x3C9
#define DAC_SHIFT          2

#define FFT_BITS           9
#define FFT_SIZE           (1 << FFT_BITS)
#define BARS               32
#define BAR_WIDTH          (WIDTH / BARS)
#define BAR_MAX            (HEIGHT * 2 / 3)
#define PIXELS_PER_OCTAVE  16
#define FLOOR_OCTAVES      4
#define SCOPE_HEIGHT       40
#define SCOPE_CENTRE       (HEIGHT / 3)
#define FIRE_DECAY         4

#define BLOCKS             4
#define BLOCK_FRAMES       4096
#define HISTORY_FRAMES     65536
#define HISTORY_MASK       (HISTORY_FRAMES - 1)
#define MAX_CHANNELS       2
#define FRAME_MS           33
#define FPS_PERIOD_MS      1000

#define FOURCC(a, b, c, d) ((DWORD)(a) | (DWORD)(b) << 8 | (DWORD)(c) << 16 | (DWORD)(d) << 24)

typedef struct {
    BITMAPINFOHEADER header;
    RGBQUAD colours[COLOURS];
} palette_bitmap_info_t;

static HANDLE music = INVALID_HANDLE_VALUE;
static DWORD data_start, data_size, data_read;
static WAVEFORMATEX format;
static HWAVEOUT wave_out;
static WAVEHDR headers[BLOCKS];
static short (*block_data)[BLOCK_FRAMES * MAX_CHANNELS];
static short *history;
static DWORD queued_frames, start_tick;
static BOOL audio_open;

static HDC screen_dc, buffer_dc;
static HBITMAP buffer_bitmap;
static unsigned char *pixels;
static palette_bitmap_info_t bitmap_info;

static short twiddle_cos[FFT_SIZE / 2], twiddle_sin[FFT_SIZE / 2];
static int real_part[FFT_SIZE], imaginary_part[FFT_SIZE];
static int levels[BARS];
static int bar_bins[BARS + 1];
static WCHAR status[64] = L"Starting...";

static void set_status(const WCHAR *text, int number) {
    int at = 0, digits = 0;
    WCHAR reversed[12];
    while (*text && at < 50) status[at++] = *text++;
    if (number >= 0) {
        do {
            reversed[digits++] = (WCHAR)(L'0' + number % 10);
            number /= 10;
        } while (number && digits < 11);
        while (digits) status[at++] = reversed[--digits];
    }
    status[at] = 0;
}

static void set_dword(HKEY key, const WCHAR *name, DWORD value) {
    RegSetValueExW(key, name, 0, REG_DWORD, (const BYTE *)&value, sizeof(value));
}

static HDC open_screen(void) {
    HKEY key;
    DWORD disposition;
    if (RegCreateKeyExW(HKEY_LOCAL_MACHINE, DISPLAY_KEY, 0, 0, 0, 0, 0, &key, &disposition) == ERROR_SUCCESS) {
        set_dword(key, L"CxScreen", WIDTH);
        set_dword(key, L"CyScreen", HEIGHT);
        set_dword(key, L"Bpp", 8);
        set_dword(key, L"Frequency", SCREEN_HZ);
        set_dword(key, L"PanelNumber", PANEL_NUMBER);
        set_dword(key, L"DisplayDevice", 0);
        RegCloseKey(key);
    }
    if (!CopyFileW(DRIVER_SOURCE, DRIVER_PATH, FALSE) && GetFileAttributesW(DRIVER_PATH) == 0xFFFFFFFF) return 0;
    return CreateDCW(DRIVER_NAME, 0, 0, 0);
}

static void port_write(unsigned short port, unsigned char value) {
    __asm__ volatile("outb %0, %w1" : : "a"(value), "Nd"(port));
}

static void ramp(int from, int to, int red0, int green0, int blue0, int red1, int green1, int blue1) {
    int i, span = to - from;
    for (i = from; i <= to; i++) {
        int step = i - from;
        RGBQUAD *colour = &bitmap_info.colours[i];
        colour->rgbRed = (BYTE)(red0 + (red1 - red0) * step / span);
        colour->rgbGreen = (BYTE)(green0 + (green1 - green0) * step / span);
        colour->rgbBlue = (BYTE)(blue0 + (blue1 - blue0) * step / span);
        colour->rgbReserved = 0;
    }
}

static void load_dac(void) {
    int i;
    port_write(DAC_WRITE_INDEX, 0);
    for (i = 0; i < COLOURS; i++) {
        port_write(DAC_DATA, bitmap_info.colours[i].rgbRed >> DAC_SHIFT);
        port_write(DAC_DATA, bitmap_info.colours[i].rgbGreen >> DAC_SHIFT);
        port_write(DAC_DATA, bitmap_info.colours[i].rgbBlue >> DAC_SHIFT);
    }
}

static BOOL create_buffer(void) {
    ramp(0, 63, 0, 0, 0, 40, 0, 120);
    ramp(64, 127, 40, 0, 120, 220, 0, 100);
    ramp(128, 191, 220, 0, 100, 255, 160, 0);
    ramp(192, 255, 255, 160, 0, 255, 255, 255);
    load_dac();
    bitmap_info.header.biSize = sizeof(BITMAPINFOHEADER);
    bitmap_info.header.biWidth = WIDTH;
    bitmap_info.header.biHeight = HEIGHT;
    bitmap_info.header.biPlanes = 1;
    bitmap_info.header.biBitCount = 8;
    bitmap_info.header.biCompression = BI_RGB;
    bitmap_info.header.biClrUsed = COLOURS;
    buffer_dc = CreateCompatibleDC(screen_dc);
    buffer_bitmap = CreateDIBSection(screen_dc, (BITMAPINFO *)&bitmap_info, DIB_RGB_COLORS, (void **)&pixels, 0, 0);
    if (!buffer_dc || !buffer_bitmap || !pixels) return FALSE;
    SelectObject(buffer_dc, buffer_bitmap);
    memset(pixels, 0, WIDTH * HEIGHT);
    return TRUE;
}

static unsigned char *row(int y) {
    return pixels + (HEIGHT - 1 - y) * WIDTH;
}

static BOOL read_exact(void *buffer, DWORD length) {
    DWORD got = 0;
    return ReadFile(music, buffer, length, &got, 0) && got == length;
}

static BOOL open_music(void) {
    DWORD riff[3], chunk[2];
    music = CreateFileW(MUSIC_PATH, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (music == INVALID_HANDLE_VALUE) return FALSE;
    if (!read_exact(riff, sizeof(riff)) || riff[0] != FOURCC('R', 'I', 'F', 'F') || riff[2] != FOURCC('W', 'A', 'V', 'E')) return FALSE;
    while (read_exact(chunk, sizeof(chunk))) {
        DWORD length = chunk[1] + (chunk[1] & 1);
        if (chunk[0] == FOURCC('f', 'm', 't', ' ')) {
            PCMWAVEFORMAT pcm;
            if (chunk[1] < sizeof(pcm) || !read_exact(&pcm, sizeof(pcm))) return FALSE;
            SetFilePointer(music, (LONG)(length - sizeof(pcm)), 0, FILE_CURRENT);
            format.wFormatTag = pcm.wf.wFormatTag;
            format.nChannels = pcm.wf.nChannels;
            format.nSamplesPerSec = pcm.wf.nSamplesPerSec;
            format.nAvgBytesPerSec = pcm.wf.nAvgBytesPerSec;
            format.nBlockAlign = pcm.wf.nBlockAlign;
            format.wBitsPerSample = pcm.wBitsPerSample;
        } else if (chunk[0] == FOURCC('d', 'a', 't', 'a')) {
            data_start = SetFilePointer(music, 0, 0, FILE_CURRENT);
            data_size = chunk[1];
            break;
        } else {
            SetFilePointer(music, (LONG)length, 0, FILE_CURRENT);
        }
    }
    return format.wFormatTag == WAVE_FORMAT_PCM && format.wBitsPerSample == 16 &&
           format.nChannels >= 1 && format.nChannels <= MAX_CHANNELS && data_size;
}

static DWORD read_block(short *samples) {
    DWORD frame_bytes = format.nBlockAlign, wanted = BLOCK_FRAMES * frame_bytes, got = 0, frames, i;
    if (data_read >= data_size) {
        SetFilePointer(music, (LONG)data_start, 0, FILE_BEGIN);
        data_read = 0;
    }
    if (wanted > data_size - data_read) wanted = (data_size - data_read) / frame_bytes * frame_bytes;
    if (!ReadFile(music, samples, wanted, &got, 0)) got = 0;
    data_read += wanted;
    frames = got / frame_bytes;
    for (i = 0; i < frames; i++) {
        int mono = format.nChannels == 2 ? (samples[i * 2] + samples[i * 2 + 1]) / 2 : samples[i];
        history[(queued_frames + i) & HISTORY_MASK] = (short)mono;
    }
    queued_frames += frames;
    return frames;
}

static void queue_block(int block) {
    DWORD frames = read_block(block_data[block]);
    WAVEHDR *header = &headers[block];
    if (!audio_open || !frames) return;
    if (header->dwFlags & WHDR_PREPARED) waveOutUnprepareHeader(wave_out, header, sizeof(*header));
    memset(header, 0, sizeof(*header));
    header->lpData = (LPSTR)block_data[block];
    header->dwBufferLength = frames * format.nBlockAlign;
    waveOutPrepareHeader(wave_out, header, sizeof(*header));
    waveOutWrite(wave_out, header, sizeof(*header));
}

static void start_audio(void) {
    int block;
    audio_open = waveOutOpen(&wave_out, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR;
    for (block = 0; block < BLOCKS; block++) queue_block(block);
    start_tick = GetTickCount();
}

static DWORD clock_frames(void) {
    return (GetTickCount() - start_tick) * (format.nSamplesPerSec / 100) / 10;
}

static DWORD playing_frame(void) {
    MMTIME position;
    DWORD frame = clock_frames();
    position.wType = TIME_SAMPLES;
    if (audio_open && waveOutGetPosition(wave_out, &position, sizeof(position)) == MMSYSERR_NOERROR && position.wType == TIME_SAMPLES)
        frame = position.u.sample;
    return frame;
}

static void feed_audio(void) {
    int block;
    if (audio_open) {
        for (block = 0; block < BLOCKS; block++)
            if (headers[block].dwFlags & WHDR_DONE) queue_block(block);
    } else {
        while (queued_frames < clock_frames() + FFT_SIZE && read_block(block_data[0])) {
        }
    }
}

static void stop_audio(void) {
    int block;
    if (audio_open) {
        waveOutReset(wave_out);
        for (block = 0; block < BLOCKS; block++)
            if (headers[block].dwFlags & WHDR_PREPARED) waveOutUnprepareHeader(wave_out, &headers[block], sizeof(headers[block]));
        waveOutClose(wave_out);
    }
    if (music != INVALID_HANDLE_VALUE) CloseHandle(music);
}

static void build_tables(void) {
    long long cosine = 1LL << 30, sine = 0;
    const long long step_cos = 1073660973LL, step_sin = 13176464LL;
    int i, bin = 1;
    for (i = 0; i < FFT_SIZE / 2; i++) {
        long long next_cos, next_sin;
        twiddle_cos[i] = (short)(cosine >> 15 > 32767 ? 32767 : cosine >> 15);
        twiddle_sin[i] = (short)(sine >> 15 > 32767 ? 32767 : sine >> 15);
        next_cos = (cosine * step_cos - sine * step_sin) >> 30;
        next_sin = (sine * step_cos + cosine * step_sin) >> 30;
        cosine = next_cos;
        sine = next_sin;
    }
    for (i = 0; i <= BARS; i++) {
        int edge = 1;
        int octaves = i * (FFT_BITS - 1);
        int whole = octaves / BARS, fraction = octaves % BARS;
        edge <<= whole;
        edge += edge * fraction / BARS;
        if (edge <= bin && i) edge = bin + 1;
        if (edge > FFT_SIZE / 2) edge = FFT_SIZE / 2;
        bar_bins[i] = bin = edge;
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
    return height < 0 ? 0 : height > BAR_MAX ? BAR_MAX : height;
}

static void analyse(DWORD frame) {
    DWORD first = frame > FFT_SIZE ? frame - FFT_SIZE : 0;
    int i, bar;
    if (first + FFT_SIZE > queued_frames) first = queued_frames > FFT_SIZE ? queued_frames - FFT_SIZE : 0;
    for (i = 0; i < FFT_SIZE; i++) real_part[i] = history[(first + i) & HISTORY_MASK] * hann(i) >> 15;
    transform();
    for (bar = 0; bar < BARS; bar++) {
        int bin, loudest = 0, height;
        for (bin = bar_bins[bar]; bin < bar_bins[bar + 1]; bin++) {
            int value = magnitude(bin);
            if (value > loudest) loudest = value;
        }
        height = bar_height(loudest);
        levels[bar] = height > levels[bar] ? height : levels[bar] > 4 ? levels[bar] - 4 : 0;
    }
}

static void burn(void) {
    int x, y;
    for (y = 0; y < HEIGHT - 1; y++) {
        unsigned char *line = row(y), *below = row(y + 1);
        for (x = 1; x < WIDTH - 1; x++) {
            int heat = (below[x - 1] + below[x] + below[x + 1] + line[x]) >> 2;
            line[x] = (unsigned char)(heat > FIRE_DECAY ? heat - FIRE_DECAY : 0);
        }
    }
}

static void draw_bars(void) {
    int bar, x, y;
    for (bar = 0; bar < BARS; bar++) {
        int left = bar * BAR_WIDTH + 1, right = left + BAR_WIDTH - 2;
        for (y = HEIGHT - levels[bar]; y < HEIGHT; y++) {
            unsigned char colour = (unsigned char)(160 + 95 * (HEIGHT - y) / BAR_MAX);
            unsigned char *line = row(y);
            for (x = left; x < right; x++) line[x] = colour;
        }
    }
}

static void draw_scope(DWORD frame) {
    int x, previous = SCOPE_CENTRE;
    DWORD first = frame > WIDTH ? frame - WIDTH : 0;
    for (x = 0; x < WIDTH; x++) {
        int y = SCOPE_CENTRE + history[(first + x) & HISTORY_MASK] * SCOPE_HEIGHT / 32768, from, to;
        from = y < previous ? y : previous;
        to = y < previous ? previous : y;
        if (from < 0) from = 0;
        if (to >= HEIGHT) to = HEIGHT - 1;
        for (; from <= to; from++) row(from)[x] = 255;
        previous = y;
    }
}

static void render(void) {
    DWORD frame = playing_frame();
    analyse(frame);
    burn();
    draw_bars();
    draw_scope(frame);
    BitBlt(screen_dc, 0, 0, WIDTH, HEIGHT, buffer_dc, 0, 0, SRCCOPY);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show) {
    BOOL ready = FALSE;
    DWORD frames = 0, period_start;
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    build_tables();
    block_data = LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, sizeof(*block_data) * BLOCKS);
    history = LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, sizeof(*history) * HISTORY_FRAMES);
    screen_dc = open_screen();
    if (!block_data || !history) {
        set_status(L"Out of memory", -1);
    } else if (!screen_dc) {
        set_status(L"No large screen", -1);
    } else if (!create_buffer()) {
        set_status(L"No DIB section", -1);
    } else if (!open_music()) {
        set_status(L"No 16-bit MUSIC.WAV", -1);
    } else {
        start_audio();
        set_status(audio_open ? L"Playing" : L"Silent", -1);
        ready = TRUE;
    }
    period_start = GetTickCount();
    while (autopc_app_running()) {
        DWORD started = GetTickCount(), spent;
        HDC dc;
        if (ready) {
            feed_audio();
            render();
            frames++;
            if (started - period_start >= FPS_PERIOD_MS) {
                set_status(audio_open ? L"Playing, fps " : L"Silent, fps ", (int)(frames * 1000 / (started - period_start)));
                frames = 0;
                period_start = started;
            }
        }
        dc = autopc_app_begin_draw();
        autopc_print(dc, status);
        autopc_app_end_draw(dc);
        spent = GetTickCount() - started;
        if (spent < FRAME_MS) Sleep(FRAME_MS - spent);
    }
    if (ready) stop_audio();
    if (buffer_dc) DeleteDC(buffer_dc);
    if (buffer_bitmap) DeleteObject(buffer_bitmap);
    if (screen_dc) DeleteDC(screen_dc);
    if (history) LocalFree(history);
    if (block_data) LocalFree(block_data);
    autopc_app_stop();
    return 0;
}
