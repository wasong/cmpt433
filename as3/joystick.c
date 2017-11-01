#include "joystick.h"

FILE* openFile(char* fileName, char* type) {
	FILE *file = fopen(fileName, type);
	if (file == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n", fileName);
		perror("Error");
		exit(-1);
	}

	return file;
}

void writeToFile(char* fileName, char* value) {
        FILE* file = fopen(fileName, "w");
	if (file == NULL) printf("file NULL\n");
        int charWritten = fprintf(file, "%s", value);
        if (charWritten <= 0) printf("ERROR WRITING DATA");
        fclose(file);
}

void closeFile(FILE* file) {
	// TODO: error checking
	fclose(file);
}

void nanoslip(int sec, long nano) {
	// long seconds = sec;
	// long nanoseconds = nano;
	// struct timespec reqDelay = {seconds, nanoseconds};
	// nanosleep(&reqDelay, (struct timespec *) NULL);

	struct timespec delay;
	delay.tv_sec = sec;
	delay.tv_nsec = nano;
	nanosleep(&delay, NULL);
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

void saveGPIOValue(char* fileName, char* buff) {
	FILE* file = openFile(fileName, "r");
	// Save string (line)
	fgets(buff, MAX_LENGTH, file);
	closeFile(file);
}

int readGPIOValue(char* fileName) {
	// Read string (line)
	FILE* file = openFile(fileName, "r");

	char buff[MAX_LENGTH];
	fgets(buff, MAX_LENGTH, file);

	closeFile(file);

	return atoi(buff);
}

_Bool checkIfPressed(char* pinFile) {
	int pinValue = readGPIOValue(pinFile);
	// printf("%s: %d\n", pinFile, pinValue);
	return pinValue == 0;
}

void initJoysticks() {
	exportGPIOFile(JSUP);
	exportGPIOFile(JSDN);
	exportGPIOFile(JSRT);
	exportGPIOFile(JSLFT);
	exportGPIOFile(JSPSH);
}

void* startJoystickThread(void* arg) {
	initJoysticks();
	printf("Starting joystick thread\n");
	// stopping bool from audioMixer
	while (1) {
		int tempo = AudioMixer_getBPM();
		long timeNano = ((double) 60 / tempo / 2) * 100000000;
		int timeSeconds = timeNano / 100000000;
		nanoslip(timeSeconds, timeNano);

		_Bool UP = checkIfPressed(JSUP_FILE);
		_Bool DOWN = checkIfPressed(JSDN_FILE);
		_Bool LEFT = checkIfPressed(JSLFT_FILE);
		_Bool RIGHT = checkIfPressed(JSRT_FILE);
		_Bool PUSHED = checkIfPressed(JSPSH_FILE);

		if (UP) {
			AudioMixer_setVolume(AudioMixer_getVolume() + 5);
			printf("VOL: %d\n", AudioMixer_getVolume());
			nanoslip(0, 100000000);
		}
		if (DOWN)  {
			AudioMixer_setVolume(AudioMixer_getVolume() - 5);
			printf("VOL: %d\n", AudioMixer_getVolume());
			nanoslip(0, 100000000);
		}
		if (LEFT) {
			AudioMixer_setBPM(AudioMixer_getBPM() + 5);
			printf("BPM: %d\n", AudioMixer_getBPM());
			nanoslip(0, 100000000);
		} 
		if (RIGHT) {
			AudioMixer_setBPM(AudioMixer_getBPM() - 5);
			printf("BPM: %d\n", AudioMixer_getBPM());
			nanoslip(0, 100000000);
		} 
		if (PUSHED) {
			AudioMixer_nextState();
			printf("State: %d\n", state);
			nanoslip(0, 100000000);
		}
	}
	printf("Ending joystick thread\n");
	pthread_exit(0);
}
