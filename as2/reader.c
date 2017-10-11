#include <stdlib.h>
#include <stdio.h>
#include "reader.h"

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
