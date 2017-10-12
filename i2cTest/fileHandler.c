#include "fileHandler.h"
#include <stdlib.h>
#include <stdio.h>

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


void exportGPIOPin(int pin) {
	FILE *pfile = openFile(EXPORT_FILE, "w");
	int pinWritten = fprintf(pfile, "%d", pin);
	if (pinWritten <= 0) printf("ERROR WRITING DATA");
	closeFile(pfile);
}

void writeToFile(char* fileName, char* value) {
	FILE* file = openFile(fileName, "w");
	int charWritten = fprintf(file, "%s", value);
	if (charWritten <= 0) printf("ERROR WRITING DATA");
	closeFile(file);
}
