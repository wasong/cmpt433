#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define A2D_FILE_VOLTAGE0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define A2D_VOLTAGE_REF_V 1.8
#define A2D_MAX_READING 4095

#define PIECEWISE_SZ 10

const int PIECEWISE_ARR_SZ[] = {1, 20, 60, 120, 250, 300, 500, 800, 1200, 2100};
const int PIECEWISE_POT[] = {0, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4100};

void sleep(long sec, long nano) {
	// 1 sec = sleep(0, 100000000);
	long seconds = sec;
	long nanoseconds = nano;
	struct timespec reqDelay = {seconds, nanoseconds};
	nanosleep(&reqDelay, (struct timespec *) NULL);
}

void binarySearch(int value) {
	int max = PIECEWISE_SZ - 1;
	int mid = floor(max / 2);
	int min = 0;
	int found = 1;
	while (found) {
		int potVal = PIECEWISE_POT[mid];
		// printf("Before: min: %d, mid: %d, max: %d, potVal: %d\n", min, mid, max, potVal);
		if (value < potVal) {
			// lower half
			max = mid;
			mid = floor((max - min) / 2) + min;
			// printf("Lower: min: %d, mid: %d, max: %d, potVal: %d\n", min, mid, max, potVal);
		} else if (value > potVal) {
			// upper half
			min = mid;
			mid = floor((max - mid) / 2) + mid;
			// printf("Upper: min: %d, mid: %d, max: %d, potVal: %d\n", min, mid, max, potVal);
		} else {
			// exactly the potVal
			// printf("Exactly: min: %d, mid: %d, max: %d, potVal: %d\n", min, mid, max, potVal);
			// printf("Between potValue: %d, %d\n", PIECEWISE_POT[mid], PIECEWISE_POT[max]);
			break;
			
		}
		// printf("After: min: %d, mid: %d, max: %d, potVal: %d\n", min, mid, max, potVal);

		// find 2 adjacent points
		
		int difference = max - min;
		// printf("difference: %d - %d = %d\n", max, mid, difference);
		if (difference == 1) {
			printf("Between potValue: %d, %d\n", PIECEWISE_POT[min], PIECEWISE_POT[max]);
			found = 0;
		}

		// ...work
	}
}

int getVoltage0Reading() {
	// Open file
	FILE *f = fopen(A2D_FILE_VOLTAGE0, "r");
	if (!f) {
		printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
		printf("try: echo BB-ADC > /sys/devices/platform/bone_capemgr/slots\n");
	exit(-1);
	}

	// Get reading
	int a2dReading = 0;
	int itemsRead = fscanf(f, "%d", &a2dReading);
	if (itemsRead <= 0) {
		printf("ERROR: Unable to read values from voltage input file.\n");
		exit(-1);
	}

	// Close file
	fclose(f);
	return a2dReading;
}

int main() {
	while (true) {
		int reading = getVoltage0Reading();
		double voltage = ((double)reading / A2D_MAX_READING) * A2D_VOLTAGE_REF_V;
		// printf("Value %5d ==> %5.2fV\n", reading, voltage);
		printf("--------------------------------\n");
		printf("Value %5d\n\n", reading);
		binarySearch(reading);
		printf("--------------------------------\n");
		sleep(1, 0);

	}
	return 0;
}
