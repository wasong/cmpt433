#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_LENGTH 512
#define EXPORT_FILE "/sys/class/gpio/export"
#define JSUP_FILE "/sys/class/gpio/gpio26/value"
#define JSDN_FILE "/sys/class/gpio/gpio46/value"
#define JSLFT_FILE "/sys/class/gpio/gpio65/value"
#define JSRT_FILE "/sys/class/gpio/gpio47/value"
#define JSPSH_FILE "/sys/class/gpio/gpio27/value"

FILE* openFile(char* fileName, char* type);

void closeFile(FILE* file);

void sleep(long sec, long nano);

void exportGPIOFile(int pin);

void saveGPIOValue(char* fileName, char* buff);

char* readGPIOValue(char* fileName);

_Bool checkIfPressed(char* buff);

#endif // _JOYSTICK_H_