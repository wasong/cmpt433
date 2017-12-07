#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

void initJoystickThread();
void cleanJoystickThread();

static void initializeButtonPin(void);
static _Bool readButtonWithStarterWare(void);
static _Bool readButtonWithBitTwiddling(void);

static void uartInitialize(void);
static void uartBaudRateSet(void);

#endif
