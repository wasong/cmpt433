#include "server.h"

int main()
{
	AudioMixer_init();

	pthread_t playbackId;
	pthread_t serverID;

	pthread_attr_t attributes;
	pthread_attr_init(&attributes);

	pthread_create(&playbackId, NULL, playbackThread, NULL);
	pthread_create(&serverID,&attributes,listen_for_command,NULL);

	pthread_join(playbackId, NULL);
	pthread_join(serverID,NULL);

	AudioMixer_cleanup();
	return 0;
}