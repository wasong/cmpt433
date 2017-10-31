#include "server.h"

#define SIZE 1024

//display preliminary messages for each condition
// char* displayResponse(char* respond_to_msg, char* prelimMsg)
// {
// 	memset(respond_to_msg, 0, 1024);
// 	strcat(respond_to_msg, prelimMsg);
// 	return respond_to_msg;
// }

char* displayError(char* respond_to_msg)
{
	memset(respond_to_msg, 0, sizeof(char)*SIZE);
	sprintf(respond_to_msg, "Invalid command: Please see \"help\" for list of valid commands.\n");
	return respond_to_msg;
}
 
 
char* increase_volume()
{
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	memset(respond_to_msg,0,sizeof(char)*SIZE);

		char buffer[512];
		//get volume and increment
		AudioMixer_setVolume(AudioMixer_getVolume()+ 5); 
		sprintf(buffer, "%d\n", AudioMixer_getVolume());
		strcat(respond_to_msg, "Volume: ");
		strcat(respond_to_msg, buffer);
		return respond_to_msg;
}


char* decrease_volume()
{
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	memset(respond_to_msg,0,sizeof(char)*SIZE);

		char buffer[512];
		//get volume and increment
		AudioMixer_setVolume(AudioMixer_getVolume()- 5); 
		sprintf(buffer, "%d\n", AudioMixer_getVolume());
		strcat(respond_to_msg, "Volume: ");
		strcat(respond_to_msg, buffer);
		return respond_to_msg;
}


char* increase_tempo()
{
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	memset(respond_to_msg,0,sizeof(char)*SIZE);

		char buffer[512];
		//get volume and increment
		AudioMixer_setBPM(AudioMixer_getBPM()+ 5); 
		sprintf(buffer, "%d\n", AudioMixer_getBPM());
		strcat(respond_to_msg, "Tempo: ");
		strcat(respond_to_msg, buffer);
		return respond_to_msg;
}

char* decrease_tempo()
{
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	memset(respond_to_msg,0,sizeof(char)*SIZE);

		char buffer[512];
		//get volume and increment
		AudioMixer_setBPM(AudioMixer_getBPM()- 5); 
		sprintf(buffer, "%d\n", AudioMixer_getBPM());
		strcat(respond_to_msg, "Tempo: ");
		strcat(respond_to_msg, buffer);
		return respond_to_msg;
}

char* next_beat()
{
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	memset(respond_to_msg,0,sizeof(char)*SIZE);
	
	strcat(respond_to_msg, "On to next beat\n");
	return respond_to_msg;
}

char* previous_beat()
{
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	memset(respond_to_msg,0,sizeof(char)*SIZE);
	
	strcat(respond_to_msg, "Back to previous beat\n");
	return respond_to_msg;
}

char* verifyCommand(char* myMsg, int sock, struct sockaddr_storage serverAddr)
{
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	printf("drdjdrd\n");
	//conditionals for all commands
	if(strcmp(myMsg, "help\n") == 0)
	{
		printf("djdt7ut7t7t7\n");
		memset(respond_to_msg, 0, sizeof(char)*SIZE);
		strcat(respond_to_msg, "Accepted command examples:\n");
		strcat(respond_to_msg, "volumeI  -- Increase the volume.\n");
		strcat(respond_to_msg, "volumeD  -- Decrease the volume.\n");
		strcat(respond_to_msg, "tempoI  -- Increase the tempo.\n");
		strcat(respond_to_msg, "tempoD  -- Decrease the tempo.\n");
		strcat(respond_to_msg, "beatN  -- Change to next beat.\n");
		strcat(respond_to_msg, "beatP  -- Revert to previous beat.\n");
		strcat(respond_to_msg, "stop  -- cause the server program to end.\n");
		return respond_to_msg;
	}
	if(strcmp(myMsg, "volumeI\n") == 0)
	{
		return increase_volume();
	}

	else if(strcmp(myMsg, "volumeD\n") == 0)
	{
		return decrease_volume();
	}

	else if(strcmp(myMsg, "tempoI\n") == 0)
	{
		return increase_tempo();
	}

	else if(strcmp(myMsg, "tempoD\n") == 0)
	{
		return decrease_tempo();
	}

	else
	{
		printf("11111111111111\n");
		return displayError(respond_to_msg);
	}

	return NULL;
}

void* listen_for_command(void* arg)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);       //socket initailization
	struct sockaddr_storage serverAddr;
	char myMsg[1024];
	//char stop = ' ';
	_Bool stopping = false;
	int b;

	//binding 
	struct sockaddr_in sockName;
	memset((char*)&sockName, 0, sizeof(sockName));
	sockName.sin_family = AF_INET;
	sockName.sin_port = htons(SERVER_PORT);
	sockName.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t serverAddrSize;

	if(bind(sock, (struct sockaddr *)&sockName, sizeof(sockName)))
	{
		perror("binding failed");
		exit(1);
	}
	
	serverAddrSize = sizeof(serverAddr);
	
	//send msg to server
	while((b = recvfrom(sock, myMsg, 1024, 0, (struct sockaddr *)&serverAddr, &serverAddrSize)) > 0 && !stopping)
	{
		myMsg[b] = '\0';
		printf("%d\n", myMsg[b]);
		char* msgsss = verifyCommand(myMsg, sock, serverAddr);
		printf("8888888888888888\n");
		if (strcmp(msgsss, "stop\n") == 0)
		{
		// 	stop = 'T';
		// 	sendto(sock, respond_to_msg, 1024, 0, (struct sockaddr *)&serverAddr, serverAddrSize);
		// 	free(respond_to_msg);
		// 	break;
		// } 
		// else if(strcmp(respond_to_msg, " \n") == 0)
		// {
		// 	free(respond_to_msg);
		// }
		// else
		// {
			stopping = true;
			break;
		}

		sendto(sock, msgsss, 1024, 0, (struct sockaddr *)&serverAddr, serverAddrSize);
		free(msgsss);
	}
	
	close(sock);
	pthread_exit(0);
}