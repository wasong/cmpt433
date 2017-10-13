#include "reader.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int calcPieceWise();
double calcArraySize();
int getVoltage0Reading();

const int PIECEWISE_ARR_SZ[] = {1, 20, 60, 120, 250, 300, 500, 800, 1200, 2100};
const int PIECEWISE_POT[] = {0, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4100};

int getArraySize() {
	int reading = getVoltage0Reading();
	int arraySz = calcArraySize(reading);

	return arraySz;
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

int calcPieceWise(int value, int max, int min) {
	double a = (double) PIECEWISE_POT[min];
	double b = (double) PIECEWISE_POT[max];
	double m = (double) PIECEWISE_ARR_SZ[min];
	double n = (double) PIECEWISE_ARR_SZ[max];
	double s = (double) value;

	return (int) floor(((s - a) / (b - a)) * (n - m) + m);
}

double calcArraySize(int value) {
	int max = PIECEWISE_SZ - 1;
	int mid = floor(max / 2);
	int min = 0;
	int found = 1;
	while (found) {
		int potVal = PIECEWISE_POT[mid];
		if (value < potVal) {
			// lower half
			max = mid;
			mid = floor((max - min) / 2) + min;
		} else if (value > potVal) {
			// upper half
			min = mid;
			mid = floor((max - mid) / 2) + mid;
		} else {
			// exactly the potVal
			max = mid;
		}

		// find 2 adjacent points
		
		int difference = max - min;
		if (difference == 1) {
			found = 0;
		}
		// ...work
	}

	return calcPieceWise(value, max, min);
}

