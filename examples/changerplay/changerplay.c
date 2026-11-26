#include <windows.h>
#include <mmsystem.h>
#include <string.h>

#include "autopc.h"
#include "autopc_app.h"
#include "mp3_stream.h"

#define CHANGER_DEVICE     L"CDR2:"
#define IOCTL_GET_USAGE    0xCF20
#define IOCTL_SET_USAGE    0xCF21
#define IOCTL_SELECT_SLOT  0xCF26
#define USAGE_DATA         2
#define DATA_SLOT          4
#define CHANGER_FOLDER     L"\\CD Changer\\"
#define CARD_FOLDER        L"\\Storage Card\\"
#define CARD_ROOT          L"\\Storage Card"
#define LOG_NAME           L"CHGPLAY.TXT"
#define DISC_TIMEOUT_MS    30000
#define POLL_MS            500
#define DRAW_MS            200
#define IDLE_MS            20
#define BLOCKS             4
#define OUTPUT_CHANNELS    2
#define OUTPUT_RATE        22050
#define HALVE_FROM         32000
#define HALFBAND_TAPS      7
#define HALFBAND_SHIFT     5
#define FRACTION_BITS      16
#define FRACTION_ONE       (1 << FRACTION_BITS)
#define MAX_FRAME_OUTPUT   (MP3_STREAM_MAX_SAMPLES * 3)
#define BLOCK_SAMPLES      (MAX_FRAME_OUTPUT * 4)
#define NO_ATTRIBUTES      0xFFFFFFFF
#define LOG_LINE           160

typedef struct {
    int halve;
    int odd;
    int history[OUTPUT_CHANNELS][HALFBAND_TAPS];
    DWORD step;
    DWORD position;
    int last[OUTPUT_CHANNELS];
} resampler;

static const int halfband[HALFBAND_TAPS] = { -1, 0, 9, 16, 9, 0, -1 };

static WCHAR status[96];
static HANDLE log_file = INVALID_HANDLE_VALUE;
static HANDLE changer = INVALID_HANDLE_VALUE;
static DWORD saved_usage;
static BOOL usage_changed;
static DWORD drawn_at;

static void draw(void) {
    HDC dc = autopc_app_begin_draw();
    autopc_print(dc, status);
    autopc_app_end_draw(dc);
    drawn_at = GetTickCount();
}

static void log_text(const WCHAR *text) {
    char line[LOG_LINE];
    DWORD length = 0, written;
    if (log_file == INVALID_HANDLE_VALUE) return;
    while (text[length] && length < LOG_LINE - 2) {
        line[length] = text[length] < 0x80 ? (char)text[length] : '?';
        length++;
    }
    line[length++] = '\r';
    line[length++] = '\n';
    WriteFile(log_file, line, length, &written, 0);
    FlushFileBuffers(log_file);
}

static void show(const WCHAR *text) {
    wcscpy(status, text);
    log_text(text);
    draw();
}

static BOOL wait_ms(DWORD ms) {
    DWORD started = GetTickCount();
    while (GetTickCount() - started < ms) {
        if (!autopc_app_running()) return FALSE;
        Sleep(IDLE_MS);
    }
    return TRUE;
}

static BOOL find_mp3(const WCHAR *folder, WCHAR *path) {
    WIN32_FIND_DATAW found;
    HANDLE search;
    wcscpy(path, folder);
    wcscat(path, L"*.mp3");
    search = FindFirstFileW(path, &found);
    if (search == INVALID_HANDLE_VALUE) return FALSE;
    FindClose(search);
    wcscpy(path, folder);
    wcscat(path, found.cFileName);
    return TRUE;
}

static BOOL changer_control(DWORD code, void *input, DWORD input_size, void *output, DWORD output_size) {
    DWORD returned = 0;
    WCHAR line[LOG_LINE];
    BOOL ok = DeviceIoControl(changer, code, input, input_size, output, output_size, &returned, 0);
    wsprintfW(line, L"ioctl %x size %u: %s, error %u", code, input_size, ok ? L"ok" : L"failed", ok ? 0 : GetLastError());
    log_text(line);
    return ok;
}

static void close_changer(void) {
    if (changer == INVALID_HANDLE_VALUE) return;
    if (usage_changed) changer_control(IOCTL_SET_USAGE, 0, saved_usage, 0, 0);
    CloseHandle(changer);
    changer = INVALID_HANDLE_VALUE;
}

static BOOL open_data_disc(WCHAR *path) {
    DWORD slot = DATA_SLOT, waited = 0;
    WCHAR line[LOG_LINE];
    changer = CreateFileW(CHANGER_DEVICE, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
    if (changer == INVALID_HANDLE_VALUE) {
        log_text(L"No changer (CDR2:)");
        return FALSE;
    }
    changer_control(IOCTL_GET_USAGE, 0, 0, &saved_usage, sizeof saved_usage);
    wsprintfW(line, L"Changer usage was %u", saved_usage);
    log_text(line);
    show(L"Changer: data mode");
    usage_changed = changer_control(IOCTL_SET_USAGE, 0, USAGE_DATA, 0, 0);
    show(L"Changer: loading disc 5");
    if (!changer_control(IOCTL_SELECT_SLOT, &slot, sizeof slot, 0, 0)) {
        log_text(L"No changer or no disc 5");
        close_changer();
        return FALSE;
    }
    while (waited < DISC_TIMEOUT_MS) {
        if (find_mp3(CHANGER_FOLDER, path)) return TRUE;
        wsprintfW(line, L"Waiting for disc 5... %us", waited / 1000);
        show(line);
        if (!wait_ms(POLL_MS)) return FALSE;
        waited += POLL_MS;
    }
    show(L"No MP3 in \\CD Changer");
    return FALSE;
}

static int read_file(void *context, unsigned char *buffer, int bytes) {
    DWORD got = 0;
    if (!ReadFile((HANDLE)context, buffer, (DWORD)bytes, &got, 0)) return -1;
    return (int)got;
}

static const WCHAR *leaf(const WCHAR *path) {
    const WCHAR *name = path;
    for (; *path; path++) {
        if (*path == '\\') name = path + 1;
    }
    return name;
}

static short clamp(int value) {
    return (short)(value > 32767 ? 32767 : value < -32768 ? -32768 : value);
}

static void resampler_start(resampler *state, int rate) {
    memset(state, 0, sizeof *state);
    state->halve = rate >= HALVE_FROM;
    if (state->halve) rate /= 2;
    state->step = (DWORD)(((unsigned long long)rate << FRACTION_BITS) / OUTPUT_RATE);
}

static int resample(resampler *state, const short *frame, int count, int channels, short *out) {
    int written = 0, index, channel, tap;
    for (index = 0; index < count / channels; index++) {
        int current[OUTPUT_CHANNELS];
        for (channel = 0; channel < OUTPUT_CHANNELS; channel++) current[channel] = frame[index * channels + (channels == OUTPUT_CHANNELS ? channel : 0)];
        if (state->halve) {
            for (channel = 0; channel < OUTPUT_CHANNELS; channel++) {
                int sum = 0;
                memmove(state->history[channel], state->history[channel] + 1, sizeof(int) * (HALFBAND_TAPS - 1));
                state->history[channel][HALFBAND_TAPS - 1] = current[channel];
                for (tap = 0; tap < HALFBAND_TAPS; tap++) sum += halfband[tap] * state->history[channel][tap];
                current[channel] = sum >> HALFBAND_SHIFT;
            }
            state->odd ^= 1;
            if (state->odd) continue;
        }
        while (state->position < FRACTION_ONE) {
            for (channel = 0; channel < OUTPUT_CHANNELS; channel++) {
                int last = state->last[channel];
                out[written++] = clamp(last + (int)(((long long)(current[channel] - last) * state->position) >> FRACTION_BITS));
            }
            state->position += state->step;
        }
        state->position -= FRACTION_ONE;
        for (channel = 0; channel < OUTPUT_CHANNELS; channel++) state->last[channel] = current[channel];
    }
    return written;
}

static int fill_block(mp3_stream *stream, resampler *state, short *block) {
    static short frame[MP3_STREAM_MAX_SAMPLES];
    int filled = 0, count;
    while (filled <= BLOCK_SAMPLES - MAX_FRAME_OUTPUT && (count = mp3_stream_decode(stream, frame)) > 0) {
        if (!state->step) resampler_start(state, stream->sample_rate);
        filled += resample(state, frame, count, stream->channels, block + filled);
    }
    return filled;
}

static void play(const WCHAR *path) {
    static mp3_stream stream;
    static WAVEHDR headers[BLOCKS];
    static resampler state;
    WAVEFORMATEX format;
    HWAVEOUT wave_out = 0;
    short *blocks;
    HANDLE file;
    DWORD played = 0, block;
    int queued = 0, ended = 0;
    WCHAR line[LOG_LINE];

    file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    blocks = LocalAlloc(LMEM_FIXED, sizeof(short) * BLOCK_SAMPLES * BLOCKS);
    if (file == INVALID_HANDLE_VALUE || !blocks || !mp3_stream_open(&stream, read_file, file)) {
        show(L"Can't open the MP3");
        if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
        if (blocks) LocalFree(blocks);
        return;
    }
    memset(headers, 0, sizeof headers);
    memset(&state, 0, sizeof state);
    for (block = 0; block < BLOCKS; block++) {
        int samples = fill_block(&stream, &state, blocks + block * BLOCK_SAMPLES);
        if (!samples) break;
        headers[block].lpData = (LPSTR)(blocks + block * BLOCK_SAMPLES);
        headers[block].dwBufferLength = samples * sizeof(short);
    }
    if (!stream.sample_rate) {
        show(L"Not an MP3 Helix can play");
    } else {
        memset(&format, 0, sizeof format);
        format.wFormatTag = WAVE_FORMAT_PCM;
        format.nChannels = OUTPUT_CHANNELS;
        format.nSamplesPerSec = OUTPUT_RATE;
        format.wBitsPerSample = 16;
        format.nBlockAlign = (WORD)(format.nChannels * sizeof(short));
        format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
        wsprintfW(line, L"%s: %u Hz, %u channels, %u kbps, played at %u Hz", leaf(path), stream.sample_rate, stream.channels, stream.bitrate / 1000, OUTPUT_RATE);
        log_text(line);
        MMRESULT opened = waveOutOpen(&wave_out, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL);
        if (opened != MMSYSERR_NOERROR) {
            wsprintfW(line, L"Can't open wave output: %u", opened);
            show(line);
            wave_out = 0;
        }
    }
    if (wave_out) {
        for (block = 0; block < BLOCKS && headers[block].dwBufferLength; block++) {
            waveOutPrepareHeader(wave_out, &headers[block], sizeof headers[block]);
            waveOutWrite(wave_out, &headers[block], sizeof headers[block]);
            queued++;
        }
        while (queued && autopc_app_running()) {
            for (block = 0; block < BLOCKS; block++) {
                WAVEHDR *header = &headers[block];
                int samples;
                if (!(header->dwFlags & WHDR_DONE)) continue;
                waveOutUnprepareHeader(wave_out, header, sizeof *header);
                played += header->dwBufferLength / format.nBlockAlign;
                header->dwFlags = 0;
                queued--;
                samples = ended ? 0 : fill_block(&stream, &state, blocks + block * BLOCK_SAMPLES);
                if (!samples) {
                    ended = 1;
                    header->dwBufferLength = 0;
                    continue;
                }
                header->dwBufferLength = samples * sizeof(short);
                waveOutPrepareHeader(wave_out, header, sizeof *header);
                waveOutWrite(wave_out, header, sizeof *header);
                queued++;
            }
            if (GetTickCount() - drawn_at >= DRAW_MS) {
                DWORD seconds = played / OUTPUT_RATE;
                wsprintfW(status, L"%s %u:%02u", leaf(path), seconds / 60, seconds % 60);
                draw();
            }
            Sleep(IDLE_MS);
        }
        waveOutReset(wave_out);
        for (block = 0; block < BLOCKS; block++) {
            if (headers[block].dwFlags & WHDR_PREPARED) waveOutUnprepareHeader(wave_out, &headers[block], sizeof headers[block]);
        }
        waveOutClose(wave_out);
        wsprintfW(line, L"Played %s: %u s", leaf(path), played / OUTPUT_RATE);
        show(line);
    }
    mp3_stream_close(&stream);
    CloseHandle(file);
    LocalFree(blocks);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR command_line, int show_command) {
    WCHAR path[MAX_PATH];
    BOOL found;
    if (!autopc_app_start(instance, 0, 0)) return 1;
    autopc_init();
    if (GetFileAttributesW(CARD_ROOT) != NO_ATTRIBUTES) log_file = autopc_card_create(LOG_NAME);
    show(L"Changer Play");
    found = open_data_disc(path);
    if (!found && changer == INVALID_HANDLE_VALUE) found = find_mp3(CARD_FOLDER, path);
    if (found) {
        show(leaf(path));
        play(path);
    } else if (changer == INVALID_HANDLE_VALUE) {
        show(L"No changer and no MP3 on the card");
    }
    close_changer();
    while (autopc_app_running()) {
        if (GetTickCount() - drawn_at >= DRAW_MS) draw();
        Sleep(IDLE_MS);
    }
    if (log_file != INVALID_HANDLE_VALUE) CloseHandle(log_file);
    autopc_app_stop();
    return 0;
}
