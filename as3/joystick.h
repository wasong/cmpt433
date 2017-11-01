#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "audioMixer_template.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 512
#define JSUP 26
#define JSDN 46
#define JSLFT 65
#define JSRT 47
#define JSPSH 27
#define EXPORT_FILE "/sys/class/gpio/export"
#define JSUP_FILE "/sys/class/gpio/gpio26/value"
#define JSDN_FILE "/sys/class/gpio/gpio46/value"
#define JSLFT_FILE "/sys/class/gpio/gpio65/value"
#define JSRT_FILE "/sys/class/gpio/gpio47/value"
#define JSPSH_FILE "/sys/class/gpio/gpio27/value"

FILE* openFile(char* fileName, char* type);

void writeToFile(char* fileName, char* value);

void exportGPIOFile(int pin);

void closeFile(FILE* file);

void nanoslip(int sec, long nano);

void exportGPIOFile(int pin);

void saveGPIOValue(char* fileName, char* buff);

int readGPIOValue(char* fileName);

_Bool checkIfPressed(char* pinFile);

void initJoystick(int pin);

void* startJoystickThread(void* arg);

#endif // _JOYSTICK_H_
