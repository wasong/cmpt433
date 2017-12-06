#include "dmtimer.h"
#include "soc_AM335x.h"
#include "beaglebone.h"
#include "error.h"
#include "watchdog.h"

#include "wdtimer.h"


/******************************************************************************
 **                      WATCHDOG FUNCTIONS
 *******************************************************************************/
#define WD_CLOCK          (32000L)
#define WD_TIMEOUT_S      (30)
#define WD_TIMEOUT_TICKS  (WD_TIMEOUT_S * WD_CLOCK)
#define WD_RESET_VALUE    ((unsigned int)0xFFFFFFFF - WD_TIMEOUT_TICKS + 1)

void Watchdog_init()
{
	WatchdogTimer1ModuleClkConfig();
	WatchdogTimerReset(SOC_WDT_1_REGS);
	WatchdogTimerDisable(SOC_WDT_1_REGS);
	WatchdogTimerPreScalerClkDisable(SOC_WDT_1_REGS);
	WatchdogTimerReloadSet(SOC_WDT_1_REGS, WD_RESET_VALUE);
	WatchdogTimerEnable(SOC_WDT_1_REGS);
}

void Watchdog_hit(void)
{
	static unsigned int triggerCounter = 0;

	// Hit the WD, giving it a new trigger each time to keep it from
	// resetting the board.
	triggerCounter++;

	WatchdogTimerTriggerSet(SOC_WDT_1_REGS, triggerCounter);
}

