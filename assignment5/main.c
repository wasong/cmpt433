// Fake Typing bare metal sample application
// On the serial port, fakes

#include "consoleUtils.h"
#include <stdint.h>

// My hardware abstraction modules
#include "serial.h"
#include "timer.h"
#include "wdtimer.h"
// My application's modules
#include "leds.h"
#include "fakeTyper.h"
#include "joystick.h"
#include <stdbool.h>

static volatile uint8_t s_rxByte = 0;
static volatile _Bool stopWatchDog = false;

static void serialRxIsrCallback(uint8_t rxByte) {
	s_rxByte = rxByte;
}

static void doBackgroundSerialWork(void)
{
	if (s_rxByte != 0) {
		if (s_rxByte == '?') {
			ConsoleUtilsPrintf(" Commands:\n?   : Display this help message.\n0-9 : Set speed 0 (slow) to 9 (fast).\na   : Select pattern A (bounce).\nb   : Select pattern B (bar).\nx   : Stop hitting the watchdog.\nBTN : Push-button to toggle mode.\n");
		} else if (s_rxByte == 'a'){
			ConsoleUtilsPrintf("\nChanging to bounce mode.\n");
			bounceLEDPattern();
		} else if (s_rxByte == 'b'){
			ConsoleUtilsPrintf("\nChanging to bar mode.\n");
			barLEDPattern();
		} else if (s_rxByte == '0'){
			ConsoleUtilsPrintf("\nSetting LED speed to 0\n");
			// TODO: handle speed change
			// TODO: handle other digits
		} else if (s_rxByte == 'x'){
			ConsoleUtilsPrintf("\nNo longer hitting the watchdog\n");
			stopWatchDog = true;
		} else {
			ConsoleUtilsPrintf("\nInvalid command\n");
		}

		s_rxByte = 0;
	}
}

int main(void) {
	// Initialization
	Serial_init(serialRxIsrCallback);
	Timer_init();
	Watchdog_init();
	FakeTyper_init();

	initLEDS();
	initJoystick();

	// Setup callbacks from hardware abstraction modules to application:
	Serial_setRxIsrCallback(serialRxIsrCallback);
	Timer_setTimerIsrCallback(FakeTyper_notifyOnTimeIsr);
	Timer_setTimerIsrCallback(joystickNotifyOnTimeIsr);

	// Display startup messages to console:
	ConsoleUtilsPrintf("\n CMPT 433 Assignment 5 - Vaanyi Igiri, Andrew Song\n");
	ConsoleUtilsPrintf(" Commands:\n?   : Display this help message.\n0-9 : Set speed 0 (slow) to 9 (fast).\na   : Select pattern A (bounce).\nb   : Select pattern B (bar).\nx   : Stop hitting the watchdog.\nBTN : Push-button to toggle mode.\n");

	// Main loop:
	while(1) {
		// Handle background processing
		doBackgroundSerialWork();
		FakeTyper_doBackgroundWork();
		joystickDoBackgroundWork();

		// Timer ISR signals intermittent background activity.
		if(Timer_isIsrFlagSet()) {
			Timer_clearIsrFlag();

			if(!stopWatchDog){
				Watchdog_hit();
			}
		}
	}
}
