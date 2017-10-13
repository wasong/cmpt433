#include "fileHandler.h"
#include "sleep.h"
#include "reader.h"
#include "display.h"
#include "I2C.h"
#include "server.h"
#include "sorter.h"
#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

void* displayThread();
void* arraySizeThread();

int numSorted;

void run() {
	// initial setup
	initDisplay();
	
	// execute thread switch
	pthread_t displayThr;
	pthread_t arraySizeThr;
	pthread_t sorterThread;
	pthread_t serverThread;

	// attributes
	pthread_attr_t attributes;
	pthread_attr_init(&attributes);

	// create threads and run fn
	pthread_create(&displayThr, NULL, displayThread, NULL);
	pthread_create(&arraySizeThr, NULL, arraySizeThread, NULL);
	pthread_create(&sorterThread, &attributes, sorter_startSorting, NULL);
	pthread_create(&serverThread, &attributes, listen_for_command, NULL);

	pthread_join(displayThr, NULL);
	pthread_join(arraySizeThr, NULL);
	pthread_join(sorterThread, NULL);
	pthread_join(serverThread, NULL);
}

void* displayThread() {
	initDisplay();
	int i2cFileDesc = initI2C();

	while (stop != 'T') {
		writeNumber(i2cFileDesc, numSorted);
	}
	printf("Stopped display thread\n");
	endI2C(i2cFileDesc);
	pthread_exit(0);
}

void* arraySizeThread() {
	while (stop != 'T') {
		int arraySz = getArraySize();
		pthread_mutex_lock(&mutex);
		arrLength = arraySz;
		numSorted = numSortedArr;
		numSortedArr = 0;
		pthread_mutex_unlock(&mutex);
		slip(1, 0);
	}
	printf("Stopped potentiometer thread\n");
	pthread_exit(0);
}

