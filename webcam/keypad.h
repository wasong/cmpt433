// Controls 12-button keypad
// in: 3.3v
// out: (LEFT -> RIGHT) GPIO 88, 89, 86, 87, 10, 9, 8, 78, 76, 74, 72, 71

#ifndef _KEYPAD_H
#define _KEYPAD_H

typedef struct code_t { int size; char *code; } code_t;

void Keypad_init();
void Keypad_unInit();

void Keypad_setCode(int size, char *new_code);
code_t Keypad_getCode();

void Keypad_setAlarm(int value);
int Keypad_getAlarm();

int Keypad_getCodeEntered();

#endif
