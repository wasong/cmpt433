// Playback sounds in real time, allowing multiple simultaneous wave files
// to be mixed together and played without jitter.
#ifndef AUDIO_MIXER_H
#define AUDIO_MIXER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <limits.h>
#include <alloca.h> // needed for mixer

#define HI_HAT "beatbox-wav-files/100053__menegass__gui-drum-cc.wav"
#define BASE "beatbox-wav-files/100051__menegass__gui-drum-bd-hard.wav"
#define SNARE "beatbox-wav-files/100059__menegass__gui-drum-snare-soft.wav"

typedef struct {
	int numSamples;
	short *pData;
} wavedata_t;

#define AUDIOMIXER_MAX_VOLUME 100

_Bool stopping;

int rock_status;
wavedata_t rock1[3];

void nanoSleepFunc(int a, int b);

// init() must be called before any other functions,
// cleanup() must be called last to stop playback threads and free memory.
void initBeat();
void AudioMixer_reset();
void AudioMixer_init(void);
void AudioMixer_cleanup(void);
long AudioMixer_getSleepTime(void);

// Read the contents of a wave file into the pSound structure. Note that
// the pData pointer in this structure will be dynamically allocated in
// readWaveFileIntoMemory(), and is freed by calling freeWaveFileData().
void AudioMixer_readWaveFileIntoMemory(char *fileName, wavedata_t *pSound);
void AudioMixer_freeWaveFileData(wavedata_t *pSound);

// Queue up another sound bite to play as soon as possible.
void AudioMixer_queueSound(wavedata_t *pSound);

// Get/set the volume.
// setVolume() function posted by StackOverflow user "trenki" at:
// http://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code
int  AudioMixer_getVolume();
void AudioMixer_setVolume(int newVolume);

int AudioMixer_getBPM();
void AudioMixer_setBPM(int newBPM);

char* AudioMixer_getBeat(int beat_num);

void* playbackThread(void* arg);

#endif