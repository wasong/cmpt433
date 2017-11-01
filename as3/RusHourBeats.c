#include "audioMixer_template.h"
#include "RusHourBeats.h"
#include "joystick.h"

void rock()
{
	int tempo = AudioMixer_getBPM();
	long timeNano = ((double) 60 / tempo / 2) * 100000000;
	int timeSeconds = timeNano / 100000000;

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[0]);
	nanoslip(timeSeconds, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	nanoslip(timeSeconds, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[1]);
	nanoslip(timeSeconds, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	nanoslip(timeSeconds, timeNano);
}

void rockSequence() {
	rock();
	rock();
}

void custom()
{
//implement custom beat
}

void noBeat()
{
	return;
}

void* beatThread(void* arg)
{
	BeatBoxInit();
	while(1)
	{
		if(state == 0)
		{
			noBeat();
		}
		if(state == 1)
		{
			rockSequence();
		}
		if(state == 2)
		{
			custom();
		}
		nanoSleepFunc(1, 0);
	}
	pthread_exit(0);
}

