#include "udpserver.h"
#include "joystick.h"
#include "beats.h"

int main()
{
	AudioMixer_init();

	pthread_t playbackThreadId;
	pthread_t serverID;
	pthread_t joystickID;
	pthread_t beatsID;
	printf("Declared IDs\n");

	pthread_attr_t attributes;
	pthread_attr_init(&attributes);
	printf("Declared attributes\n");

	pthread_create(&playbackThreadId, NULL, playbackThread, NULL);
	pthread_create(&serverID,&attributes,server_thread,NULL);
	pthread_create(&joystickID,&attributes,joystickThread,NULL);
	pthread_create(&beatsID,&attributes,beat_pattern_thread,NULL);
	printf("Created threads\n");

	pthread_join(playbackThreadId, NULL);
	pthread_join(serverID,NULL);
	pthread_join(joystickID, NULL);
	pthread_join(beatsID, NULL);

	AudioMixer_cleanup();
	return 0;
}