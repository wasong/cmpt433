#include "audioMixer_template.h"
#include "RusHourBeats.h"
#include "joystick.h"

void rock()
{
	int tempo = AudioMixer_getBPM();
	long timeNano = ((double) 60 / tempo / 2) * 1000000000;

	printf("%li\n", timeNano);
	
	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[1]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	nanoSleepFunc(0, timeNano);
}

void rockSequence() {
	rock();
	rock();
}

void custom()
{
	int tempo = AudioMixer_getBPM();
	long timeNano = ((double) 60 / tempo / 2) * 1000000000;

	printf("%li\n", timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[1]);
	nanoSleepFunc(1, timeNano);

	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[1]);
	nanoSleepFunc(0, timeNano);
	//
	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[1]);
	nanoSleepFunc(1, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[1]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[0]);
	nanoSleepFunc(0, timeNano);

	AudioMixer_queueSound(&beatArr[2]);
	AudioMixer_queueSound(&beatArr[1]);
	nanoSleepFunc(0, timeNano);
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
		// nanoSleepFunc(1, 0);
	}
	pthread_exit(0);
}

