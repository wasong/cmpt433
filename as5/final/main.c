#include "leds.h"
#include "joystick.h"

int main(void)
{
	// Initialization
  initJoystickThread();
  initializeLeds(); // not thread

  barLeds();
  bounceLeds();
  cleanJoystickThread();

}
