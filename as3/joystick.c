#include "joystick.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_LENGTH 1024
#define EXPORT_FILE "/sys/class/gpio/export"
#define JSUP_FILE "/sys/class/gpio/gpio26/value"
#define JSDN_FILE "/sys/class/gpio/gpio46/value"
#define JSLFT_FILE "/sys/class/gpio/gpio65/value"
#define JSRT_FILE "/sys/class/gpio/gpio47/value"
#define JSPSH_FILE "/sys/class/gpio/gpio27/value"

FILE* openFile(char* fileName, char* type) {
	FILE *file = fopen(fileName, type);
	if (file == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n", fileName);
		perror("Error");
		exit(-1);
	}

	return file;
}

void closeFile(FILE* file) {
	// TODO: error checking
	fclose(file);
}

void sleep(long sec, long nano) {
	long seconds = sec;
	long nanoseconds = nano;
	struct timespec reqDelay = {seconds, nanoseconds};
	nanosleep(&reqDelay, (struct timespec *) NULL);
}

void exportGPIOFile(int pin) {
	FILE *pfile = fopen(EXPORT_FILE, "w");
	fprintf(pfile, "%d", pin);

	if (pfile == NULL) {
		printf("ERROR: Unable to open the file.\n");
		exit(1);
	}

	fclose(pfile);
}

void saveGPIOValue(char* buff) {
	FILE* file = openFile(JSUP_FILE, "r");
	// Save string (line)
	fgets(buff, MAX_LENGTH, file);
	closeFile(file);
}

char* readGPIOValue(char* fileName) {
	// Read string (line)
	FILE* file = openFile(fileName, "r");

	printf("Reading: '%s'", fileName);
	char buff[MAX_LENGTH];
	fgets(buff, MAX_LENGTH, file);
    printf("Read: '%s'", buff);

    closeFile(file);
    
    return buff;
}

_Bool checkIfPressed(char* buff) {
	return strcmp("0", buff) == 0;
}
