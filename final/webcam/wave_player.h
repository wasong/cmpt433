// Playback sounds in real time, allowing multiple simultaneous wave files
// to be mixed together and played without jitter.
#ifndef WAVE_PLAYER_H
#define WAVE_PLAYER_H

#include <alsa/asoundlib.h>

typedef struct {
	int numSamples;
	short *pData;
} wavedata_t;

snd_pcm_t *Audio_openDevice();
void Audio_readWaveFileIntoMemory(char *fileName, wavedata_t *pWaveStruct);
void Audio_playFile(snd_pcm_t *handle, wavedata_t *pWaveData);
void AudioMixer_setVolume(int newVolume);
void* soundThread(void* arg);

void sound_init(void);
void sound_join();


#endif