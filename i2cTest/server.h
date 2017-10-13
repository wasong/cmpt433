/******************************************************************/
//server-related function declarations
#ifndef _SERVER_H_
#define _SERVER_H_

#include "sorter.h"
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
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

// Helper for "count" command
// Writes output of total # of sorted arrays to buffer
char* countBuffer(char* respond_to_msg, char* msg_count);

// Helper for "get" command
// Writes the nth element of current permutation
char* getNumDisplay(char* respond_to_msg, char* myMsg, int position);

// Helper for "get length" command
// Outputs size of array
char* getLengthBuffer(char* respond_to_msg, char* msg_getLength);

char* getArrayDisplay(char* respond_to_msg, int sock, struct sockaddr_storage serverAddr);

// Facilitates specific response messages for each valid command  
char* verifyCommand(char* myMsg, int sock, struct sockaddr_storage serverAddr);

#endif

// Receive messages from socket
void* listen_for_command(void* arg);
