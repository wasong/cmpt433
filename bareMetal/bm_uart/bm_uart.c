/**
 * Simple UART demo.
 */

#include "uart_irda_cir.h"
#include "soc_AM335x.h"
#include "beaglebone.h"
#include "consoleUtils.h"
#include "hw_types.h"
//#include "watchdog.h"

/******************************************************************************
 **              INTERNAL MACRO DEFINITIONS
 ******************************************************************************/
#define BAUD_RATE_115200          (115200)
#define UART_MODULE_INPUT_CLK     (48000000)

/******************************************************************************
 **              INTERNAL FUNCTION PROTOTYPES
 ******************************************************************************/
static void UartInitialize(void);
static void UartBaudRateSet(void);


/******************************************************************************
 **              GLOBAL VARIABLE DEFINITIONS
 ******************************************************************************/

/******************************************************************************
 **              FUNCTION DEFINITIONS
 ******************************************************************************/

int main()
{
	unsigned long counter = 0;

	UartInitialize();

	ConsoleUtilsPrintf("Demo bare metal UART application\n");
	ConsoleUtilsPrintf("All this application does is print this message and some\n");
	ConsoleUtilsPrintf("more lines while runing.\n");
	ConsoleUtilsPrintf("Note: This may reset in about 45seconds... why?\n");

	while(1) {
		counter++;
		if (counter % 10000000 == 0) {
			ConsoleUtilsPrintf("Count = %u\n", counter);

			// Hit the watchdog (must #include "watchdog.h"
			// Each time you hit the WD, must pass it a different number
			// than the last time you hit it.
			// WatchdogTimerTriggerSet(SOC_WDT_1_REGS, counter);
		}
	}
}



static void UartInitialize()
{
	/* Configuring the system clocks for UART0 instance. */
	UART0ModuleClkConfig();
	/* Performing the Pin Multiplexing for UART0 instance. */
	UARTPinMuxSetup(0);
	/* Performing a module reset. */
	UARTModuleReset(SOC_UART_0_REGS);
	/* Performing Baud Rate settings. */
	UartBaudRateSet();
	/* Switching to Configuration Mode B. */
	UARTRegConfigModeEnable(SOC_UART_0_REGS, UART_REG_CONFIG_MODE_B);
	/* Programming the Line Characteristics. */
	UARTLineCharacConfig(SOC_UART_0_REGS,
			(UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
			UART_PARITY_NONE);
	/* Disabling write access to Divisor Latches. */
	UARTDivisorLatchDisable(SOC_UART_0_REGS);
	/* Disabling Break Control. */
	UARTBreakCtl(SOC_UART_0_REGS, UART_BREAK_COND_DISABLE);
	/* Switching to UART16x operating mode. */
	UARTOperatingModeSelect(SOC_UART_0_REGS, UART16x_OPER_MODE);
	/* Select the console type based on compile time check */
	ConsoleUtilsSetType(CONSOLE_UART);
}


/*
 ** A wrapper function performing Baud Rate settings.
 */
static void UartBaudRateSet(void)
{
	unsigned int divisorValue = 0;

	/* Computing the Divisor Value. */
	divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
			BAUD_RATE_115200,
			UART16x_OPER_MODE,
			UART_MIR_OVERSAMPLING_RATE_42);

	/* Programming the Divisor Latches. */
	UARTDivisorLatchWrite(SOC_UART_0_REGS, divisorValue);
}
