#ifndef DISPLAY_H_
#define DISPLAY_H_

#define LEFT_DIGIT_DIR "/sys/class/gpio/gpio61/direction"
#define RIGHT_DIGIT_DIR "/sys/class/gpio/gpio44/direction"
#define LEFT_DIGIT_VAL "/sys/class/gpio/gpio61/value"
#define RIGHT_DIGIT_VAL "/sys/class/gpio/gpio44/value"

void initDisplay();

void showLeft();

void showRight();

#endif // DISPLAY_H_
