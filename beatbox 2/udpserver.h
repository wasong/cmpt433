#ifndef _UDPSERVER_H_
#define _UDPSERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "audioMixer_template.h"

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define SERVER_PORT 12345

// Displays list of valid commands
char* command_help(void);

char* command_volume_up();

char* command_volume_down();

char* command_tempo_up();

char* command_tempo_down();

char* command_beat_up();

char* command_beat_down();

char* command_invalid();
// Controls which function to call based on passed-in command
// and returns an appropriate char* message according aforementioned command
char* command_controller(char* command);

// Starts server_thread to be listening for client to
// send it commands and reply accordingly
void* server_thread(void* arg);

#endif