#ifndef DISPLAY_H_
#define DISPLAY_H_

#define LEFT_DIGIT_DIR "/sys/class/gpio/gpio61/direction"
#define RIGHT_DIGIT_DIR "/sys/class/gpio/gpio44/direction"
#define LEFT_DIGIT_VAL "/sys/class/gpio/gpio61/value"
#define RIGHT_DIGIT_VAL "/sys/class/gpio/gpio44/value"
#define ZERO_L  0xA1
#define ZERO_U  0x86
#define ONE_L   0x80
#define ONE_U   0x02
#define TWO_L   0x31
#define TWO_U   0x0E
#define THREE_L 0xB0
#define THREE_U 0x0E
#define FOUR_L  0x90
#define FOUR_U  0x8A
#define FIVE_L  0xB0
#define FIVE_U  0x8C
#define SIX_L   0xB1
#define SIX_U   0x8C
#define SEVEN_L 0x80
#define SEVEN_U 0x06
#define EIGHT_L 0xB1
#define EIGHT_U 0x8E
#define NINE_L  0x90
#define NINE_U  0x8E

void initDisplay();

void showLeft();
void hideLeft();

void showRight();
void hideRight();

#endif // DISPLAY_H_
