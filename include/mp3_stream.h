#ifndef BRAINPLAY_MP3_STREAM_H
#define BRAINPLAY_MP3_STREAM_H

#define MP3_STREAM_INPUT_BYTES 16384
#define MP3_STREAM_MAX_SAMPLES (1152 * 2)

typedef int (*mp3_read_function)(void *context, unsigned char *buffer, int bytes);

typedef struct {
    void *decoder;
    mp3_read_function read;
    void *read_context;
    unsigned char input[MP3_STREAM_INPUT_BYTES];
    int filled;
    int offset;
    int end_of_input;
    int skip;
    int started;
    long audio_start;
    int not_mp3;
    int sample_rate;
    int channels;
    int bitrate;
} mp3_stream;

int mp3_stream_open(mp3_stream *stream, mp3_read_function read, void *read_context);
void mp3_stream_close(mp3_stream *stream);
int mp3_stream_decode(mp3_stream *stream, short *samples);
void mp3_stream_restart(mp3_stream *stream);

#endif
