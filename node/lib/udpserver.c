#include "udpserver.h"


#define RESPOND_SIZE 512

// SERVER CODE STARTS HERE
char* command_help()
{
	char* reply_msg = (char *)malloc(sizeof(char)*RESPOND_SIZE);
	memset(reply_msg,0,sizeof(char)*RESPOND_SIZE);
	strcat(reply_msg,"Valid commands:\nvolume+ \t-- increment volume\n");
	strcat(reply_msg,"volume- \t-- decrement volume\n");
	strcat(reply_msg,"tempo+ \t-- increment tempo.\n");
	strcat(reply_msg,"tempo- \t-- decrement tempo.\n");
	strcat(reply_msg,"beat+ \t-- next beat.\n");
	strcat(reply_msg,"beat- \t-- previous beat.\n");
	strcat(reply_msg,"stop \t-- terminate the program.\n");
	return reply_msg;
}

char* command_volume_up()
{
	char* reply_msg = (char *)malloc(sizeof(char)*RESPOND_SIZE);
	memset(reply_msg,0,sizeof(char)*RESPOND_SIZE);
	/*
	 *  INCREMENT volume here
	 */
	AudioMixer_setVolume(AudioMixer_getVolume() + 5);

	char buff[512];
	sprintf(buff,"%d\n", AudioMixer_getVolume());
	strcat(reply_msg,"Volume: ");
	strcat(reply_msg, buff);
	return reply_msg;
}

char* command_volume_down()
{
	char* reply_msg = (char *)malloc(sizeof(char)*RESPOND_SIZE);
	memset(reply_msg,0,sizeof(char)*RESPOND_SIZE);
	/*
	 *  DECREMENT volume here
	 */
	AudioMixer_setVolume(AudioMixer_getVolume() - 5);
	char buff[512];
	sprintf(buff,"%d\n", AudioMixer_getVolume());
	strcat(reply_msg,"Volume: ");
	strcat(reply_msg, buff);
	return reply_msg;
}

char* command_tempo_up()
{
	char* reply_msg = (char *)malloc(sizeof(char)*RESPOND_SIZE);
	memset(reply_msg,0,sizeof(char)*RESPOND_SIZE);
	/*
	 *  INCREMENT tempo here
	 */
	AudioMixer_setBPM(AudioMixer_getBPM() + 5);
	char buff[512];
	sprintf(buff,"%d\n", AudioMixer_getBPM());
	strcat(reply_msg,"Tempo: ");
	strcat(reply_msg, buff);
	return reply_msg;
}

char* command_tempo_down()
{
	char* reply_msg = (char *)malloc(sizeof(char)*RESPOND_SIZE);
	memset(reply_msg,0,sizeof(char)*RESPOND_SIZE);
	/*
	 *  DECREMENT tempo here
	 */
	AudioMixer_setBPM(AudioMixer_getBPM() - 5);
	char buff[512];
	sprintf(buff,"%d\n", AudioMixer_getBPM());
	strcat(reply_msg,"Tempo: ");
	strcat(reply_msg, buff);
	return reply_msg;
}

char* command_beat_up()
{
	char* reply_msg = (char *)malloc(sizeof(char)*RESPOND_SIZE);
	memset(reply_msg,0,sizeof(char)*RESPOND_SIZE);
	/*
	 *  INCREMENT beat here
	 */
	strcat(reply_msg,"Beat incremented");
	return reply_msg;
}

char* command_beat_down()
{
	char* reply_msg = (char *)malloc(sizeof(char)*RESPOND_SIZE);
	memset(reply_msg,0,sizeof(char)*RESPOND_SIZE);
	/*
	 *  DECREMENT beat here
	 */
	strcat(reply_msg,"Beat decremented");
	return reply_msg;
}

char* command_invalid()
{
	char* reply_msg = (char *)malloc(sizeof(char)*RESPOND_SIZE);
	memset(reply_msg,0,sizeof(char)*RESPOND_SIZE);
	strcat(reply_msg,"Invalid command: Consult the \"help\" command\n");
	return reply_msg;
}

char* command_controller(char* command)
{	
	printf("%s", command);
	if(strcmp(command, "help\n") == 0)
	{
		return command_help();
	}
	if(strcmp(command,"volume+\n") == 0)
	{
		return command_volume_up();
	}
	if(strcmp(command,"volume-\n") == 0)
	{
		return command_volume_down();
	}
	if(strcmp(command,"tempo+\n") == 0)
	{
		return command_tempo_up();
	}
	if(strcmp(command,"tempo-\n") == 0)
	{
		return command_tempo_down();
	}
	else
	{
		return command_invalid();
	}
	

	return NULL;
}

void* server_thread(void* arg)
{
	// initializing varaibles
	char command[1024];
	int sock;
	struct sockaddr_in name;
	struct sockaddr_storage clientAddr;
	socklen_t client_size;
	int nBytes;

	// creating socket
	sock = socket(AF_INET, SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("Opening datagram socket\n");
		exit(1);
	}

	// initializing network information
	bzero((char *) &name, sizeof(name));
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	name.sin_port = htons(SERVER_PORT);

	// binding to a particular port, after port has been initialized
	if(bind(sock,(struct sockaddr *) &name, sizeof(name)))
	{
		perror("binding datagram socket\n");
		exit(1);
	}

	// size of the client's info
	client_size = sizeof(clientAddr);
	while((nBytes = recvfrom(sock,command,1024,0,(struct sockaddr *)&clientAddr,&client_size)) > 0
		&& !stopping)
	{
		command[nBytes] = '\0'; // set the last value in command to a null terminating character

		if(strcmp(command,"stop\n") == 0)
		{
			// printf("STOP COMMAND DETECTED!\n");
			stopping = true;
			break;
		}
		
		char* response = command_controller(command);
		
		sendto(sock,response,strlen(response),0,(struct sockaddr *)&clientAddr,client_size);
		free(response);
	}

	close(sock);
	pthread_exit(0);
}
