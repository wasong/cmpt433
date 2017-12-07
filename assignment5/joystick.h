#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

void initJoystick();

void uartInitialize(void);
void uartBaudRateSet(void);
void joystickNotifyOnTimeIsr(void);
void joystickDoBackgroundWork(void);

#endif
