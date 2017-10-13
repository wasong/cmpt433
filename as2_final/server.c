#include "server.h"

char stop = ' ';

//display preliminary messages for each condition
char* displayResponse(char* respond_to_msg, char* prelimMsg)
{
	memset(respond_to_msg, 0, 1024);
	strcat(respond_to_msg, prelimMsg);
	return respond_to_msg;
}

char* displayError(char* respond_to_msg)
{
	memset(respond_to_msg, 0, 1024);
	sprintf(respond_to_msg, "Invalid command: Please see \"help\" for list of valid commands.\n");
	return respond_to_msg;
}
 
 //helper for "count" command
char* countBuffer(char* respond_to_msg, char* msg_count)
{
		char buffer[1024];
		sprintf(buffer, "%d\n", numSortedArr);
		strcat(respond_to_msg, buffer);
		return respond_to_msg;
}

//helper for "get n" command
char* getNumDisplay(char* respond_to_msg, char* myMsg, int position)
{
	memset(respond_to_msg, 0, 1024);
	char buffer[500];
	strcat(respond_to_msg, "Value ");
	sprintf(buffer, "%d = %d\n", position, globArray[position - 1]);
	strcat(respond_to_msg, buffer);
	return respond_to_msg;
}

//helper for "get length" command
char* getLengthBuffer(char* respond_to_msg, char* msg_getLength)
{
		char buffer[500];
		sprintf(buffer, "%d\n", arrLength);
		strcat(respond_to_msg, buffer);
		return respond_to_msg;
}

char* getArrayDisplay(char* respond_to_msg, int sock, struct sockaddr_storage serverAddr)
{
	memset(respond_to_msg, 0, (sizeof(int)*4000));
	char buffer[arrLength + (sizeof(int)*4000)];
	int idx = 0;		

	//critical section begins
	pthread_mutex_lock(&mutex);
	for(int i = 0; i < arrLength; i++)
	{
		if((i % 10 == 0) && (i != 0))
		{
			idx += sprintf(buffer, "\n");
		}
		else
		{
			idx += sprintf(buffer, "%d, ", globArray[i]);
		}
			strcat(respond_to_msg, buffer);

			if(i % 74 == 0)
			{
				sendto(sock, respond_to_msg, (sizeof(int)*4000), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
				memset(respond_to_msg, 0, (sizeof(int)*4000));
			}
	}

	strcat(respond_to_msg, "\n");
	sendto(sock, respond_to_msg, (sizeof(int)*4000), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	pthread_mutex_unlock(&mutex);
	//critical section ends here
	memset(respond_to_msg, 0, (sizeof(int)*4000));
	strcat(respond_to_msg, " \n");
	return respond_to_msg;
}

char* verifyCommand(char* myMsg, int sock, struct sockaddr_storage serverAddr)
{
	char* respond_to_msg = (char*)malloc(sizeof(int)*4000);
	char myMsg_getNum[10];
	int position = -1;
	sscanf(myMsg, "%s %d", myMsg_getNum, &position);

	//conditionals for all commands
	if(strcmp(myMsg, "help\n") == 0)
	{
		memset(respond_to_msg, 0, 1024);
		strcat(respond_to_msg, "Accepted command examples:\n");
		strcat(respond_to_msg, "count  -- display number of arrays sorted.\n");
		strcat(respond_to_msg, "get length  -- display length of array currently being sorted.\n");
		strcat(respond_to_msg, "get array  --display  the full array being sorted.\n");
		strcat(respond_to_msg, "get n  -- display the nth element of array currently being sorted.\n");
		strcat(respond_to_msg, "stop  -- cause the server program to end.\n");
		return respond_to_msg;
	}
	if(strcmp(myMsg, "count\n") == 0)
	{
		respond_to_msg = displayResponse(respond_to_msg, "Number of arrays sorted = ");
		return countBuffer(respond_to_msg, myMsg);
	}

	else if(strcmp(myMsg, "get length\n") == 0)
	{
		respond_to_msg = displayResponse(respond_to_msg, "Current array length = ");
		return getLengthBuffer(respond_to_msg, myMsg);
	}

	else if(strcmp(myMsg, "get array\n") == 0)
	{
		return getArrayDisplay(respond_to_msg, sock, serverAddr);
	}

	else if(strcmp(myMsg, "stop\n") == 0)
	{
		return displayResponse(respond_to_msg, "Program Terminating\n");
	}

	else if(strcmp(myMsg_getNum, "get") == 0)
	{
		if((position <= 0)|| (position > arrLength))
		{
			memset(respond_to_msg, 0, 1024);
			sprintf(respond_to_msg, "Invalid argument. Must be between 1 and %d\n", arrLength);
			return respond_to_msg;
		}
		else
		{
			return getNumDisplay(respond_to_msg, myMsg, position);
		}
	}
	else
	{
		return displayError(respond_to_msg);
	}
}

void* listen_for_command(void* arg)
{
	printf("Started Server\n");
	int sock = socket(AF_INET, SOCK_DGRAM, 0);       //socket initailization
	struct sockaddr_storage serverAddr;
	char myMsg[1024];
	// char stop = ' ';
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
	while((b = recvfrom(sock, myMsg, 1024, 0, (struct sockaddr *)&serverAddr, &serverAddrSize)) > 0 && stop == ' ')
	{
		myMsg[b] = '\0';
		char* respond_to_msg = verifyCommand(myMsg, sock, serverAddr);
		if (strcmp(respond_to_msg, "Program Terminating\n") == 0)
		{
			stop = 'T';
			sendto(sock, respond_to_msg, 1024, 0, (struct sockaddr *)&serverAddr, serverAddrSize);
			free(respond_to_msg);
			break;
		} 
		else if(strcmp(respond_to_msg, " \n") == 0)
		{
			free(respond_to_msg);
		}
		else
		{
			sendto(sock, respond_to_msg, 1024, 0, (struct sockaddr *)&serverAddr, serverAddrSize);
			free(respond_to_msg);
		}
	}
	
	close(sock);
	printf("Exited server\n");
	pthread_exit(0);
}
