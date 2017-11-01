#include "server.h"
#include "joystick.h"

int main()
{
	AudioMixer_init();

	pthread_t playbackId;
	pthread_t serverID;
	pthread_t joystickID;

	pthread_attr_t attributes;
	pthread_attr_init(&attributes);
	printf("Initialize attributes\n");

	pthread_create(&playbackId, NULL, playbackThread, NULL);
	pthread_create(&serverID, &attributes, listen_for_command, NULL);
	pthread_create(&joystickID, &attributes, startJoystickThread, NULL);

	printf("Create threads\n");

	pthread_join(playbackId, NULL);
	pthread_join(serverID, NULL);
	pthread_join(joystickID, NULL);
	printf("Join threads\n");

	AudioMixer_cleanup();
	printf("Clean up\n");
	return 0;
}
