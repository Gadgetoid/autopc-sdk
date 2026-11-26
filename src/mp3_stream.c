#include <string.h>

#include "mp3dec.h"
#include "mp3_stream.h"

#define ID3_HEADER_BYTES 10
#define ID3_FOOTER_FLAG 0x10
#define MPEG_LAYER_3 3
#define CONTAINER_MAGIC_BYTES 8

static int refill(mp3_stream *stream)
{
    int remaining = stream->filled - stream->offset;

    if (stream->end_of_input)
        return 0;
    memmove(stream->input, stream->input + stream->offset, remaining);
    stream->filled = remaining;
    stream->offset = 0;
    while (stream->filled < MP3_STREAM_INPUT_BYTES) {
        int count = stream->read(stream->read_context, stream->input + stream->filled, MP3_STREAM_INPUT_BYTES - stream->filled);

        if (count <= 0) {
            stream->end_of_input = 1;
            break;
        }
        stream->filled += count;
    }
    return stream->filled > remaining;
}

static int skip_input(mp3_stream *stream)
{
    while (stream->skip > 0) {
        int available = stream->filled - stream->offset;
        int step = available < stream->skip ? available : stream->skip;

        stream->offset += step;
        stream->skip -= step;
        if (stream->skip > 0 && !refill(stream))
            return 0;
    }
    return 1;
}

static void find_id3_tag(mp3_stream *stream)
{
    const unsigned char *header = stream->input + stream->offset;

    if (stream->filled - stream->offset < ID3_HEADER_BYTES || memcmp(header, "ID3", 3))
        return;
    stream->skip = ID3_HEADER_BYTES + ((header[6] & 0x7f) << 21 | (header[7] & 0x7f) << 14 | (header[8] & 0x7f) << 7 | (header[9] & 0x7f));
    if (header[5] & ID3_FOOTER_FLAG)
        stream->skip += ID3_HEADER_BYTES;
}

static int is_other_container(const unsigned char *bytes, int available)
{
    if (available < CONTAINER_MAGIC_BYTES)
        return 0;
    return !memcmp(bytes + 4, "ftyp", 4) || !memcmp(bytes, "OggS", 4) || !memcmp(bytes, "fLaC", 4) || !memcmp(bytes, "RIFF", 4);
}

static int is_standard_rate(int rate)
{
    static const int rates[] = { 8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000 };
    int index;

    for (index = 0; index < (int)(sizeof(rates) / sizeof(rates[0])); index++)
        if (rates[index] == rate)
            return 1;
    return 0;
}

int mp3_stream_open(mp3_stream *stream, mp3_read_function read, void *read_context)
{
    memset(stream, 0, sizeof(*stream));
    stream->read = read;
    stream->read_context = read_context;
    stream->decoder = MP3InitDecoder();
    return stream->decoder != 0;
}

void mp3_stream_close(mp3_stream *stream)
{
    if (stream->decoder)
        MP3FreeDecoder(stream->decoder);
    stream->decoder = 0;
}

void mp3_stream_restart(mp3_stream *stream)
{
    stream->filled = 0;
    stream->offset = 0;
    stream->end_of_input = 0;
    stream->skip = 0;
    stream->started = 1;
}

int mp3_stream_decode(mp3_stream *stream, short *samples)
{
    for (;;) {
        unsigned char *frame;
        int sync, bytes_left, result;
        MP3FrameInfo info;

        if (stream->filled - stream->offset < 2 * MAINBUF_SIZE)
            refill(stream);
        if (!stream->started) {
            find_id3_tag(stream);
            stream->audio_start = stream->skip;
            stream->started = 1;
            if (!stream->skip && is_other_container(stream->input + stream->offset, stream->filled - stream->offset)) {
                stream->not_mp3 = 1;
                return 0;
            }
        }
        if (!skip_input(stream))
            return 0;
        if (stream->filled == stream->offset)
            return 0;

        sync = MP3FindSyncWord(stream->input + stream->offset, stream->filled - stream->offset);
        if (sync < 0) {
            stream->offset = stream->filled;
            if (stream->end_of_input)
                return 0;
            continue;
        }
        stream->offset += sync;

        frame = stream->input + stream->offset;
        bytes_left = stream->filled - stream->offset;
        result = MP3Decode(stream->decoder, &frame, &bytes_left, samples, 0);
        if (result == ERR_MP3_INDATA_UNDERFLOW) {
            if (stream->end_of_input)
                return 0;
            if (!refill(stream))
                return 0;
            continue;
        }
        if (result == ERR_MP3_MAINDATA_UNDERFLOW) {
            stream->offset = (int)(frame - stream->input);
            continue;
        }
        if (result) {
            stream->offset++;
            continue;
        }
        stream->offset = (int)(frame - stream->input);
        MP3GetLastFrameInfo(stream->decoder, &info);
        if (info.layer != MPEG_LAYER_3 || !is_standard_rate(info.samprate) || info.nChans < 1 || info.nChans > 2)
            continue;
        if (stream->sample_rate && (info.samprate != stream->sample_rate || info.nChans != stream->channels))
            continue;
        stream->sample_rate = info.samprate;
        stream->channels = info.nChans;
        stream->bitrate = info.bitrate;
        return info.outputSamps;
    }
}
