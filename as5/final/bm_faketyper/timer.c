// timers.c: Handle 10ms timer
#include "soc_AM335x.h"
#include "beaglebone.h"
#include "error.h"
#include "interrupt.h"
#include "dmtimer.h"

#include "serial.h"
#include "timer.h"

/******************************************************************************
 **                     TIMER TICK FUNCTIONS
 *******************************************************************************/
#define TIMER_INITIAL_COUNT             (0xFFE00000)  // Some time that looks good.
#define TIMER_RLD_COUNT                 TIMER_INITIAL_COUNT

static void DMTimerAintcConfigure(void);
static void DMTimerSetUp(void);
static void DMTimerIsr(void);

static volatile _Bool s_flagIsr = 0;
static void (*s_isrCallback)(void) = 0;

void Timer_init(void)
{
	/* This function will enable clocks for the DMTimer2 instance */
	DMTimer2ModuleClkConfig();

	/* Enable IRQ in CPSR */
	IntMasterIRQEnable();

	/* Register DMTimer2 interrupts on to AINTC */
	DMTimerAintcConfigure();

	/* Perform the necessary configurations for DMTimer */
	DMTimerSetUp();

	// Extra setup:
	// ..Select clock
	// ..Set prescaler
	DMTimerPreScalerClkDisable(SOC_DMTIMER_2_REGS);

	/* Enable the DMTimer interrupts */
	DMTimerIntEnable(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_EN_FLAG);

	/* Start the DMTimer */
	DMTimerEnable(SOC_DMTIMER_2_REGS);
}

_Bool Timer_isIsrFlagSet(void)
{
	return s_flagIsr;
}
void Timer_clearIsrFlag(void)
{
	s_flagIsr = false;
}

void Timer_setTimerIsrCallback(void (*isrCallback)(void)) {
	s_isrCallback = isrCallback;
}

// Timer ISR
static void DMTimerIsr(void)
{
	/* Disable the DMTimer interrupts */
	DMTimerIntDisable(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_EN_FLAG);

	/* Clear the status of the interrupt flags */
	DMTimerIntStatusClear(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_IT_FLAG);

	// --------------------------------------------------------
	// Work done in the ISR:
	// .. Record ISR state for background task to poll.
	s_flagIsr = true;

	// .. Call user's ISR function (if any)
	if (s_isrCallback != 0) {
		s_isrCallback();
	}

	// --------------------------------------------------------

	/* Enable the DMTimer interrupts */
	DMTimerIntEnable(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_EN_FLAG);
}




static void DMTimerAintcConfigure(void)
{
	/* Initialize the ARM interrupt control */
	// NOTE: Must disable this, otherwise clears any already established
	// interrupts, such as the serial Rx.
	//IntAINTCInit();

	/* Registering DMTimerIsr */
	IntRegister(SYS_INT_TINT2, DMTimerIsr);

	/* Set the priority */
	IntPrioritySet(SYS_INT_TINT2, 0, AINTC_HOSTINT_ROUTE_IRQ);

	/* Enable the system interrupt */
	IntSystemEnable(SYS_INT_TINT2);
}

static void DMTimerSetUp(void)
{
	/* Load the counter with the initial count value */
	DMTimerCounterSet(SOC_DMTIMER_2_REGS, TIMER_INITIAL_COUNT);

	/* Load the load register with the reload count value */
	DMTimerReloadSet(SOC_DMTIMER_2_REGS, TIMER_RLD_COUNT);

	/* Configure the DMTimer for Auto-reload and compare mode */
	DMTimerModeConfigure(SOC_DMTIMER_2_REGS, DMTIMER_AUTORLD_NOCMP_ENABLE);
}


