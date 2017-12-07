#include "leds.h"
#include "joystick.h"
#include "consoleUtils.h"


int main(void)
{

	uartInitialize();

	ConsoleUtilsPrintf("Demo bare metal UART application\n");
	ConsoleUtilsPrintf("All this application does is print this message and some\n");
	ConsoleUtilsPrintf("more lines while runing.\n");
	ConsoleUtilsPrintf("Note: This may reset in about 45seconds... why?\n");

	// Initialization
	initializeLeds(); // not thread

	barLeds();
	bounceLeds();

}
