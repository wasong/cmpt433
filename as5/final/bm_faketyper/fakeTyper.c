// fakeTyper.c: Module to simulate typing on the screen.
#include "fakeTyper.h"
#include "consoleUtils.h"
#include <stdbool.h>
/******************************************************************************
 **              Variables
 ******************************************************************************/
static volatile _Bool s_isTimeToPrintChar = false;
static const char *s_message = 0;


/******************************************************************************
 **              Public functions
 ******************************************************************************/
void FakeTyper_init(void)
{
	// Often would have something to do here in other modules,
	// so included here as just a sample.
}

void FakeTyper_setMessage(const char *newMessage)
{
	s_message = newMessage;
}

void FakeTyper_notifyOnTimeIsr(void)
{
	s_isTimeToPrintChar = true;
}

void FakeTyper_doBackgroundWork(void)
{
	if (s_isTimeToPrintChar) {
		s_isTimeToPrintChar = false;

		// Do we have a message, and not at its end?
		if (s_message && *s_message) {
			ConsoleUtilsPutChar(*s_message);
			s_message++;
		}
	}
}

