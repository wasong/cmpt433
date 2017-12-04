#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
#include "keypad.h"
#include "door_sensor.h"
#include "grabber.h"

#define SIZE 1024

//display preliminary messages for each condition
// char* displayResponse(char* respond_to_msg, char* prelimMsg)
// {
// 	memset(respond_to_msg, 0, 1024);
// 	strcat(respond_to_msg, prelimMsg);
// 	return respond_to_msg;
// }

static pthread_t serverThreadID;

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

	char buffer[512]; // data
	//get volume and increment
	sprintf(buffer, "%d\n", <data>);
	strcat(respond_to_msg, "someLabel: ");
	strcat(respond_to_msg, buffer);
	return respond_to_msg;
}
*/

char* getPasscode()
{
  char *response = (char *) malloc(sizeof(char) * SIZE);
  memset(response, 0, sizeof(char) * SIZE);

  char buffer[512];
  code_t code = Keypad_getCode();
  sprintf(buffer, "%s\n", code.code);
  strcat(response, buffer);
  return response;
}

char* getAlarm() {
  char *response = (char *) malloc(sizeof(char) * SIZE);
  memset(response, 0, sizeof(char) * SIZE);

  char buffer[512];
  sprintf(buffer, "%d\n", Keypad_getAlarm());
  strcat(response, buffer);
  return response;
}

char* isDoorOpen() {
  char *response = (char *) malloc(sizeof(char) * SIZE);
  memset(response, 0, sizeof(char) * SIZE);

  char buffer[512];
  sprintf(buffer, "%d\n", Door_isOpen());
  strcat(response, buffer);
  return response;
}

char* isCamActive() {
  char *response = (char *) malloc(sizeof(char) * SIZE);
  memset(response, 0, sizeof(char) * SIZE);

  char buffer[512];
  sprintf(buffer, "%d\n", working);
  strcat(response, buffer);
  return response;
}

// param should be of the format "size code" ie. "4 7890"
void setPasscode(char *code)
{
  code = strtok(NULL, " ");
  printf("1: %s\n",code);
  int length = atoi(code);
  code = strtok(NULL, " ");
  printf("2: %s\n", code);

  Keypad_setCode(length, code);
}

// param should be an int as a string
void setAlarm(char *sound)
{
  int alarm = atoi(sound);

  Keypad_setAlarmSound(alarm);
}

char* displayOk(char *msg)
{
  char *response = (char *) malloc(sizeof(char) * SIZE);
  memset(response, 0, sizeof(char)*SIZE);
  strcat(response, "OK\n");
  return response;
}

char* tryCode(char *code)
{
  char *response = (char *) malloc(sizeof(char) * SIZE);
  memset(response, 0, sizeof(char) * SIZE);

  char buffer[512];
  sprintf(buffer, "%d\n", Keypad_tryCode(code));
  strcat(response, "result: ");
  strcat(response, buffer);
  return response;
}

char* verifyCommand(char* myMsg, int sock, struct sockaddr_storage serverAddr)
{
  printf("received: '%s'\n", myMsg);
	char* respond_to_msg = (char*)malloc(sizeof(char)*SIZE);
	printf("Listening...\n");
	//conditionals for all commands
	if (strcmp(myMsg, "help\n") == 0)
	{
		memset(respond_to_msg, 0, sizeof(char)*SIZE);
		strcat(respond_to_msg, "Accepted command examples:\n");
		return respond_to_msg;
	} else if (strcmp(myMsg, "getCode") == 0) {
	  printf("doing getCode\n");
	  return getPasscode();
	} else if (strcmp(myMsg, "getAlarm") == 0) {
	  return getAlarm();
	} else if (strcmp(myMsg, "getDoor") == 0) {
	  return isDoorOpen();
	} else if (strcmp(myMsg, "getCam") == 0) {
	  return isCamActive();
	} else {
	  char *token = strtok(myMsg, " ");

	  if (token == NULL)
	    return displayError(respond_to_msg);
	  
	  if (strcmp(token, "setCode") == 0) {
	    // set passcode
	    if (token != NULL) {
	      printf("am i here\n");
	      setPasscode(token);
	      return displayOk(respond_to_msg);
	    }
	  } else if (strcmp(token, "setSound") == 0) {
	    // set alarm sound
	    if (token != NULL) {
	      setAlarm(token);
	      return displayOk(respond_to_msg);
	    }
	  } else if (strcmp(token, "tryCode") == 0) {
	    // try code
	    if (token != NULL) {
	      return tryCode(token);
	    }
	  } else {
	    // unknown command
	    return displayError(respond_to_msg);
	  }
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

void server_init(void){
    pthread_create(&serverThreadID, NULL, listen_for_command, NULL);
}

void server_join(){
    pthread_join(serverThreadID, NULL);
}
