/**
 * Simple UART demo with Watchdog hits to prevent reboot and Rx Interrupt.
 */

#include "uart_irda_cir.h"
#include "soc_AM335x.h"
#include "interrupt.h"
#include "beaglebone.h"
#include "consoleUtils.h"
#include "hw_types.h"
#include "watchdog.h"

/******************************************************************************
 **              INTERNAL MACRO DEFINITIONS
 ******************************************************************************/
#define BAUD_RATE_115200          (115200)
#define UART_MODULE_INPUT_CLK     (48000000)

/******************************************************************************
 **              INTERNAL FUNCTION PROTOTYPES
 ******************************************************************************/
static void UartInitialize(void);
static void UARTIsr(void);
static void UartInterruptEnable(void);
static void UartBaudRateSet(void);

/******************************************************************************
 **              GLOBAL VARIABLE DEFINITIONS
 ******************************************************************************/
volatile unsigned char rxByte = 0;
volatile unsigned long rxTextAsciiSum = 0;

/******************************************************************************
 **              FUNCTION DEFINITIONS
 ******************************************************************************/

int main()
{
	unsigned long counter = 0;

	UartInitialize();

	ConsoleUtilsPrintf("Demo bare metal UART application with Rx Interrupts\n");

	while(1)
	{
		// Check for new character:
		if (rxByte != 0) {
			ConsoleUtilsPrintf("--> %c\n", rxByte);
			rxByte = 0;
		}

		// Do the usual counter:
		counter++;
		if (counter % 1000000 == 0) {
			ConsoleUtilsPrintf("Count = %10u,  ASCII Sum %5d\n", counter, rxTextAsciiSum);

			// Hit the watchdog (must #include "watchdog.h"
			// Each time you hit the WD, must pass it a different number
			// than the last time you hit it.
			WatchdogTimerTriggerSet(SOC_WDT_1_REGS, counter);
		}
	}
}

/*
 ** Interrupt Service Routine for UART.
 */
static void UARTIsr(void)
{
	unsigned int intId = 0;

	/* Checking the source of UART interrupt. */
	intId = UARTIntIdentityGet(SOC_UART_0_REGS);

	switch(intId) {

	case UART_INTID_RX_THRES_REACH:
		rxByte = UARTCharGetNonBlocking(SOC_UART_0_REGS);
		//UARTCharPutNonBlocking(SOC_UART_0_REGS, rxByte);
		rxTextAsciiSum += rxByte;
		break;

	default:
		break;
	}

}


/*********************************************************
 *                  UART Initialization
 *********************************************************/

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
	/* Performing Interrupt configurations. */
	UartInterruptEnable();
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

/*
 ** A wrapper function performing Interrupt configurations.
 */
static void UartInterruptEnable(void)
{
	/* Enabling IRQ in CPSR of ARM processor. */
	IntMasterIRQEnable();

	/* Configuring AINTC to receive UART0 interrupts. */
	/* ..Initializing the ARM Interrupt Controller. */
	IntAINTCInit();
	/* ..Registering the Interrupt Service Routine(ISR). */
	IntRegister(SYS_INT_UART0INT, UARTIsr);
	/* ..Setting the priority for the system interrupt in AINTC. */
	IntPrioritySet(SYS_INT_UART0INT, 0, AINTC_HOSTINT_ROUTE_IRQ);
	/* ..Enabling the system interrupt in AINTC. */
	IntSystemEnable(SYS_INT_UART0INT);

	/* Enabling the specified UART interrupts. */
	UARTIntEnable(SOC_UART_0_REGS, (UART_INT_RHR_CTI));
}

