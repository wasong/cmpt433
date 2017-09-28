/*
	JSUP  Joystick Up    P8 #14 26
	JSRT  Joystick Right P8 #15 47
	JSDN  Joystick Down  P8 #16 46
	JSLFT Joystick Left  P8 #18 65
*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_LENGTH 1024

void exportGPIOFile(int pin) {
	printf("Called %s, %d\n", "/sys/class/gpio/export", pin);
	FILE *pfile = fopen("/sys/class/gpio/export", "w");

	if (pfile == NULL) {
		printf("ERROR: Unable to open the file.\n");
		exit(1);
	}

	fprintf(pfile, "%d\n", pin);

	fclose(pfile);
}

void readGPIOValue(char *fileName) {
	// "/sys/class/gpio/gpio[pin]"
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n", fileName);
		exit(-1);
	}

	// Read string (line)
	char buff[MAX_LENGTH];
	fgets(buff, MAX_LENGTH, file);

	// Close
	fclose(file);
	printf("Read: %s\n", buff);
}


int main() {
	printf("Hello embedded world, from Andrew Song!\n");

	exportGPIOFile(26);

	readGPIOValue("/sys/class/gpio/gpio26/value");

	return 0;
}
