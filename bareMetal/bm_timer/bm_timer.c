/**
 * \file   bm_timer.c
 *
 * \brief  Sample application for DMTimer.
 *
 *         Application Configuration:
 *
 *             Modules Used:
 *                 DMTimer2
 *                 UART0
 *
 *             Configurable parameters:
 *                 None.
 *
 *             Hard-coded configuration of other parameters:
 *                 Mode of Timer - Timer mode(Auto reload)
 *
 */


#include "consoleUtils.h"
#include "soc_AM335x.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "dmtimer.h"
#include "error.h"
#include "watchdog.h"

/******************************************************************************
 **                      INTERNAL MACRO DEFINITIONS
 *******************************************************************************/
#define TIMER_INITIAL_COUNT             (0xFE8287C0) // 1s w/o prescaler
//#define TIMER_INITIAL_COUNT             (0xFD050F80) // 2s w/o prescaler
#define TIMER_RLD_COUNT                 TIMER_INITIAL_COUNT

/******************************************************************************
 **                      INTERNAL FUNCTION PROTOTYPES
 *******************************************************************************/
static void uartInit(void);
static void timerInit(void);
static void DMTimerAintcConfigure(void);
static void DMTimerSetUp(void);
static void DMTimerIsr(void);

/******************************************************************************
 **                      INTERNAL VARIABLE DEFINITIONS
 *******************************************************************************/
static volatile unsigned int isrCounter = 0;
static volatile unsigned int flagIsr = 0;

/******************************************************************************
 **                          FUNCTION DEFINITIONS
 *******************************************************************************/
// Timer ISR
static void DMTimerIsr(void)
{
	/* Disable the DMTimer interrupts */
	DMTimerIntDisable(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_EN_FLAG);

	/* Clear the status of the interrupt flags */
	DMTimerIntStatusClear(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_IT_FLAG);

	flagIsr = 1;
	isrCounter++;

	/* Enable the DMTimer interrupts */
	DMTimerIntEnable(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_EN_FLAG);
}


int main(void)
{
	uartInit();
	timerInit();

	ConsoleUtilsPrintf("Counting with a timer:\n");

	unsigned int mainLoopCounter = 0;
	while(1) {
		if(flagIsr == 1) {
			mainLoopCounter++;
			ConsoleUtilsPrintf("\rMain Loop %4d,    ISR %4d",mainLoopCounter, isrCounter);
			flagIsr = 0;

			// Hit the watchdog (must #include "watchdog.h"
			// Each time you hit the WD, must pass it a different number
			// than the last time you hit it.
			WatchdogTimerTriggerSet(SOC_WDT_1_REGS, mainLoopCounter);
		}
	}

	/* Stop the DMTimer - Not that we ever get here, but this is how */
	DMTimerDisable(SOC_DMTIMER_2_REGS);
}


/******************************************************************************
 **                       INITIALIZATION FUNCTIONS
 *******************************************************************************/

static void uartInit(void)
{
	/* Initialize the UART console */
	ConsoleUtilsInit();

	/* Select the console type based on compile time check */
	ConsoleUtilsSetType(CONSOLE_UART);

}

static void timerInit(void)
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

/*
 ** Do the necessary DMTimer configurations on to AINTC.
 */
static void DMTimerAintcConfigure(void)
{
	/* Initialize the ARM interrupt control */
	IntAINTCInit();

	/* Registering DMTimerIsr */
	IntRegister(SYS_INT_TINT2, DMTimerIsr);

	/* Set the priority */
	IntPrioritySet(SYS_INT_TINT2, 0, AINTC_HOSTINT_ROUTE_IRQ);

	/* Enable the system interrupt */
	IntSystemEnable(SYS_INT_TINT2);
}

/*
 ** Setup the timer for one-shot and compare mode.
 */
static void DMTimerSetUp(void)
{
	/* Load the counter with the initial count value */
	DMTimerCounterSet(SOC_DMTIMER_2_REGS, TIMER_INITIAL_COUNT);

	/* Load the load register with the reload count value */
	DMTimerReloadSet(SOC_DMTIMER_2_REGS, TIMER_RLD_COUNT);

	/* Configure the DMTimer for Auto-reload and compare mode */
	DMTimerModeConfigure(SOC_DMTIMER_2_REGS, DMTIMER_AUTORLD_NOCMP_ENABLE);
}


