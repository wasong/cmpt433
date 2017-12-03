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


/*
char* base_function() {
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	memset(respond_to_msg,0,sizeof(char)*SIZE);

	char buffer[512];
	//get volume and increment
	sprintf(buffer, "%d\n", <data>);
	strcat(respond_to_msg, "Volume: ");
	strcat(respond_to_msg, buffer);
	return respond_to_msg;
}
*/

char* verifyCommand(char* myMsg, int sock, struct sockaddr_storage serverAddr)
{
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	printf("Listening...\n");
	//conditionals for all commands
	if (strcmp(myMsg, "help\n") == 0)
	{
		memset(respond_to_msg, 0, sizeof(char)*SIZE);
		strcat(respond_to_msg, "Accepted command examples:\n");
		return respond_to_msg;
	}
	// base structure for if statement
	// if (strcmp(myMsg, "strToCmp\n") == 0) {
	// 	return someFunc();
	// }
	else {
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
		printf("Message break: %d\n", myMsg[b]);
		char* msgsss = verifyCommand(myMsg, sock, serverAddr);
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
