#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "audioMixer_template.h"

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define SERVER_PORT 12345

// Displays list of valid commands

void joystick_setup(int pin);

void joystick_init();

int read_file_to_screen(char* filename);

int readLineFromFile(char* file_name, char* buff, unsigned int max_length);

_Bool isJoystickPressed(int pin);

void* joystickThread(void* arg);

#endif