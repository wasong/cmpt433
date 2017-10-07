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
#define LED_TRIGGER_FILE "/sys/class/leds/beaglebone:green:usr0/trigger"
#define LED_DELAY_ON_FILE "/sys/class/leds/beaglebone:green:usr0/delay_on"
#define LED_DELAY_OFF_FILE "/sys/class/leds/beaglebone:green:usr0/delay_off"
#define LED_BRIGHTNESS_FILE "/sys/class/leds/beaglebone:green:usr0/brightness"

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

void readGPIOValue() {
	// Read string (line)
	FILE* jsupFile = openFile(JSUP_FILE, "r");

	printf("Reading: '%s'", JSUP_FILE);
	char buff[MAX_LENGTH];
	fgets(buff, MAX_LENGTH, jsupFile);
	printf("Read: '%s'", buff);

	closeFile(jsupFile);
}

_Bool checkIfPressed(char* buff) {
	return strcmp("0", buff) == 0;
}


void writeToLED(char* fileName, char* value) {
	FILE* file = openFile(fileName, "w");
	int charWritten = fprintf(file, "%s", value);
	if (charWritten <= 0) printf("ERROR WRITING DATA");
	closeFile(file);
}

void flashNTimes(int times) {
	// always delay_on 100, delay_off 100
	for (int i = 0; i < times; i++) {
		writeToLED(LED_BRIGHTNESS_FILE, "1");
		sleep(0, 100000000);
		writeToLED(LED_BRIGHTNESS_FILE, "0");
		sleep(0, 100000000);
	}
}


int main() {
	printf("Hello embedded world, from Andrew Song!\n");
	exportGPIOFile(30);

	// write 'none' to LED
	writeToLED(LED_TRIGGER_FILE, "none");
	int counter = 0;
	while (counter < 10) {
		char buff[MAX_LENGTH];
		saveGPIOValue(buff);
		buff[strcspn(buff, "\n")] = 0;
		int pinVal = atoi(buff);
		//readGPIOValue();
		_Bool flag = checkIfPressed(buff);
		int times = 1;
		if (flag) times = 3;
		if (flag) {
			counter++;
			flashNTimes(times);
		} else {
			counter = 0;
			flashNTimes(times);
		}
		printf("Flashing %d time(s): Joystick = %d & counter = %d\n", times, !pinVal, counter);
		sleep(0, 600000000);
	}

	printf("Thank you for the blinks!\n");

	return 0;
}
