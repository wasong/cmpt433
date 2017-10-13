#include "fileHandler.h"
#include "sleep.h"
#include "reader.h"
#include "display.h"
#include "I2C.h"
#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

// TODO: fix globals?
int arraySize = 1;

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* displayThread();
void* arraySizeThread();

void run() {
	// initial setup
	initDisplay();
	
	// execute thread switch
	pthread_t displayThr;
	pthread_t arraySizeThr;

	// create threads and run fn
	pthread_create(&displayThr, NULL, displayThread, NULL);
	pthread_create(&arraySizeThr, NULL, arraySizeThread, NULL);

	pthread_join(displayThr, NULL);
	pthread_join(arraySizeThr, NULL);
}

void* displayThread() {
	initDisplay();
	int i2cFileDesc = initI2C();

	while (1) {
		writeNumber(i2cFileDesc, arraySize);
	}

	endI2C(i2cFileDesc);
	pthread_exit(0);
}

void* arraySizeThread() {
	while (1) {
		int arraySz = getArraySize();
		arraySize = arraySz;
		printf("Size: %d\n", arraySize);
		slip(1, 0);
	}
	pthread_exit(0);
}

