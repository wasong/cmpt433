// timer.h:
// Hardware abstraction module: The timer and its ISR functions

#ifndef _TIMER_H_
#define _TIMER_H_
#include <stdbool.h>

// Start the timer
void Timer_init(void);

// Timer tick controls:
_Bool Timer_isIsrFlagSet(void);
void Timer_clearIsrFlag(void);

// Register your own callback function
void Timer_setTimerIsrCallback(void (*isrCallback)(void));


#endif
