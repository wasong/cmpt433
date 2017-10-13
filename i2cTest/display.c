#include "fileHandler.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initDisplay() {
	// writeToFile("/sys/devices/platform/bone_capemgr/slots", "BB-I2C1");
	printf("Initiating display\n");
	exportGPIOPin(61);
	exportGPIOPin(44);
	writeToFile(LEFT_DIGIT_DIR, "out");
	writeToFile(RIGHT_DIGIT_DIR, "out");
	showLeft();
	showRight();
}

void showLeft() {
	writeToFile(LEFT_DIGIT_VAL, "1");
	writeToFile(RIGHT_DIGIT_VAL, "0");
}

void showRight() {
	writeToFile(RIGHT_DIGIT_VAL, "1");
	writeToFile(LEFT_DIGIT_VAL, "0");
}

