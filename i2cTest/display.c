#include "display.h"
#include "fileHandler.h"
#include <stdio.h>
#include <stdlib.h>

void initDisplay() {
	exportGPIOPin(61);
	exportGPIOPin(44);
	writeToFile(LEFT_DIGIT_DIR, "out");
	writeToFile(RIGHT_DIGIT_DIR, "out");
	showLeft();
	showRight();
}

void showLeft() {
	writeToFile(LEFT_DIGIT_VAL, "1");
}

void hideLeft() {
	writeToFile(LEFT_DIGIT_VAL, "0");
}

void showRight() {
	writeToFile(RIGHT_DIGIT_VAL, "1");
}

void hideRight() {
	writeToFile(RIGHT_DIGIT_VAL, "0");
}

