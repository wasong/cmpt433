/*
	JSUP  Joystick Up    P8 #14 26
	JSRT  Joystick Right P8 #15 47
	JSDN  Joystick Down  P8 #16 46
	JSLFT Joystick Left  P8 #18 65
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_LENGTH 1024
#define EXPORT_FILE "/sys/class/gpio/export"
#define JSUP_FILE "/sys/class/gpio/gpio26/value"
#define LED_TRIGGER_FILE "/sys/class/leds/beaglebone\\:green\\:usr0/trigger"
#define LED_DELAY_ON_FILE "/sys/class/leds/beaglebone\\:green\\:usr0/delay_on"
#define LED_DELAY_OFF_FILE "/sys/class/leds/beaglebone\\:green\\:usr0/delay_off"

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
	// Sleep 0.6 seconds
	long seconds = sec;
	long nanoseconds = nano;
	struct timespec reqDelay = {seconds, nanoseconds};
	nanosleep(&reqDelay, (struct timespec *) NULL);
}

void exportGPIOFile(int pin) {
	printf("Called %s, %d\n", EXPORT_FILE, pin);
	FILE *pfile = fopen(EXPORT_FILE, "w");

	if (pfile == NULL) {
		printf("ERROR: Unable to open the file.\n");
		exit(1);
	}

	fprintf(pfile, "%d\n", pin);

	fclose(pfile);
}

void saveGPIOValue(char* buff, FILE* file) {
	// Save string (line)
	fgets(buff, MAX_LENGTH, file);
}

void readGPIOValue(FILE* file) {
	// Read string (line)
	char buff[MAX_LENGTH];
	fgets(buff, MAX_LENGTH, file);
	printf("Read: '%s'", buff);
}

_Bool checkIfPressed(char* buff) {
	return strcmp("0\n", buff) != 0;
}


void writeToLED(FILE* triggerFile, char* value) {
	int charWritten = fprintf(triggerFile, "%s", value);
	if (charWritten <= 0) printf("ERROR WRITING DATA");
}

void flashNTimes(FILE* delayOn, FILE* delayOff, int times) {
	// always delay_on 100, delay_off 100
	printf("Flashing %d time(s): ", times);
	for (int i = 0; i < times; i++) {
		writeToLED(delayOn, "100");
		writeToLED(delayOff, "100");
		sleep(0, 200000000);
	}
}


int main() {
	printf("Hello embedded world, from Andrew Song!\n");
	exportGPIOFile(26);

	// open files, set char array, counter
	FILE* jsupFile = openFile(JSUP_FILE, "r");
	FILE* LEDTriggerFile = openFile(LED_TRIGGER_FILE, "w");
	FILE* LEDDelayOnFile = openFile(LED_DELAY_ON_FILE, "w");
	FILE* LEDDelayOffFile = openFile(LED_DELAY_OFF_FILE, "w");

	// write 'timer' to LED
	writeToLED(LEDTriggerFile, "timer");
	
	int counter = 0;
	while (counter < 10) {
		char buff[MAX_LENGTH];
		saveGPIOValue(buff, jsupFile);
		
		if (checkIfPressed(buff)) {
			flashNTimes(LEDDelayOnFile, LEDDelayOffFile, 3);
			counter++;
		} else if (counter == 0) {
			flashNTimes(LEDDelayOnFile, LEDDelayOffFile, 1);
			counter--;
		}
		printf("Joystick = %s ", buff);
		printf("& counter = %d\n", counter);

		sleep(0, 600000000);
	}

	closeFile(jsupFile);
	closeFile(LEDTriggerFile);
	closeFile(LEDDelayOnFile);
	closeFile(LEDDelayOffFile);
	return 0;
}
