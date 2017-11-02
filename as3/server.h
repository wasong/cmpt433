/******************************************************************/
//server-related function declarations
#ifndef _SERVER_H_
#define _SERVER_H_


#include "audioMixer_template.h"
#include "RusHourBeats.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/uio.h>
#include <sys/types.h>

#define SERVER_PORT 12345

//concatenates premilinary messages that are to appear before desired result
char* displayResponse(char* respond_to_msg, char* prelimMsg);

//Display errors for invalid entries
char* displayError(char* respond_to_msg);

char* get_volume();

char* increase_volume();

char* decrease_volume();

char* get_tempo();

char* increase_tempo();

char* decrease_tempo();

char* get_beat();

char* next_beat();

char* previous_beat();

char* playBeat(int i);

// Facilitates specific response messages for each valid command  
char* verifyCommand(char* myMsg, int sock, struct sockaddr_storage serverAddr);

// Receive messages from socket
void* listen_for_command(void* arg);

void* playbackThread(void* arg);
#endif




