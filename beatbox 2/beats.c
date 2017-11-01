#include "beats.h"
#include "audioMixer_template.h"



void rock()
{
	AudioMixer_queueSound(&rock1[0]);
	AudioMixer_queueSound(&rock1[1]);
	nanoSleepFunc(0,AudioMixer_getSleepTime());
	AudioMixer_queueSound(&rock1[0]);
	nanoSleepFunc(0,AudioMixer_getSleepTime());
	AudioMixer_queueSound(&rock1[0]);
	AudioMixer_queueSound(&rock1[2]);
	nanoSleepFunc(0,AudioMixer_getSleepTime());
	AudioMixer_queueSound(&rock1[0]);
	nanoSleepFunc(0,AudioMixer_getSleepTime());
}

void rock2()
{
	AudioMixer_queueSound(&rock1[2]);
	AudioMixer_queueSound(&rock1[0]);
	nanoSleepFunc(0,AudioMixer_getSleepTime());
	AudioMixer_queueSound(&rock1[2]);
	nanoSleepFunc(0,AudioMixer_getSleepTime());
	AudioMixer_queueSound(&rock1[2]);
	AudioMixer_queueSound(&rock1[0]);
	nanoSleepFunc(0,AudioMixer_getSleepTime());
	AudioMixer_queueSound(&rock1[2]);
	nanoSleepFunc(0,AudioMixer_getSleepTime());
}

void rockNone()
{
	return;
}

void* beat_pattern_thread(void* arg)
{
	initBeat();
	while(!stopping)
	{
		if(rock_status == 1)
		{
			rock();
		}
		if(rock_status == 2)
		{
			rock2();
		}
		if(rock_status == 0)
		{
			rockNone();
		}
		nanoSleepFunc(0,500000000);
	}

	pthread_exit(0);
}