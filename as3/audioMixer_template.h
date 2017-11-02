// Playback sounds in real time, allowing multiple simultaneous wave files
// to be mixed together and played without jitter.
#ifndef AUDIO_MIXER_H
#define AUDIO_MIXER_H

#include <alsa/asoundlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <limits.h>
#include <alloca.h> // needed for mixer

#define BASE "beatbox-wav-files/100051__menegass__gui-drum-bd-hard.wav"
#define SNARE "beatbox-wav-files/100058__menegass__gui-drum-snare-hard.wav"
#define HIHAT "beatbox-wav-files/100053__menegass__gui-drum-cc.wav"

typedef struct {
	int numSamples;
	short *pData;
} wavedata_t;


#define AUDIOMIXER_MAX_VOLUME 100

int state;
wavedata_t beatArr[3];
_Bool stopping;

void nanoSleepFunc(int x, int y);

// init() must be called before any other functions,
// cleanup() must be called last to stop playback threads and free memory.
void BeatBoxInit();
void AudioMixer_init(void);
void AudioMixer_cleanup(void);

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
void AudioMixer_setBPM(int newBPM);
int AudioMixer_getBPM();
int AudioMixer_getBeat();
void AudioMixer_nextState();
void AudioMixer_prevState();
long sleepTime();
#endif
