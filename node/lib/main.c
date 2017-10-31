#include "udpserver.h"

int main()
{
	AudioMixer_init();

	pthread_t playbackThreadId;
	pthread_t serverID;
	printf("Declared IDs\n");

	pthread_attr_t attributes;
	pthread_attr_init(&attributes);
	printf("Declared attributes\n");

	pthread_create(&playbackThreadId, NULL, playbackThread, NULL);
	pthread_create(&serverID,&attributes,server_thread,NULL);
	printf("Created threads\n");

	pthread_join(playbackThreadId, NULL);
	pthread_join(serverID,NULL);

	AudioMixer_cleanup();
	return 0;
}