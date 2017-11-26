// Example test driver:
#include <linux/module.h>

//#error Are we building this file?

// Test out printk().
static void testPrintk(void)
{
	// Display Formats:
	// printk specifiers: https://www.kernel.org/doc/Documentation/printk-formats.txt
	printk(KERN_INFO "Base 10 (%%d):         %d\n", 12345);
	printk(KERN_INFO "hex (%%x):             0x%x\n", 0x1A2B3C4F);
	printk(KERN_INFO "Ptr (%%p):             %p\n", testPrintk);
	printk(KERN_INFO "Ptr w/ symbol (%%pf):  %pf\n", testPrintk);
	printk(KERN_INFO "String (%%s):          %s\n", "Hello World!"); 
	printk(KERN_INFO "6 bytes of buffer (%%*ph): %*ph\n", 6, "Hello World!"); 

	// Log Levels:
	// Defined in: <kernel-source-path>/include/linux/kern_levels.h
	// #define	KERN_EMERG   "<0>"	/* system is unusable			*/
	// #define	KERN_ALERT   "<1>"	/* action must be taken immediately	*/
	// #define	KERN_CRIT    "<2>"	/* critical conditions			*/
	// #define	KERN_ERR     "<3>"	/* error conditions			*/
	// #define	KERN_WARNING "<4>"	/* warning conditions			*/
	// #define	KERN_NOTICE  "<5>"	/* normal but significant condition	*/
	// #define	KERN_INFO    "<6>"	/* informational			*/
	// #define	KERN_DEBUG   "<7>"	/* debug-level messages			*/

	printk(KERN_EMERG	"Level test: EMERG\n");
	printk(KERN_ALERT	"Level test: ALERT\n");
	printk(KERN_CRIT	"Level test: CRIT\n");
	printk(KERN_ERR 	"Level test: ERR\n");
	printk(KERN_WARNING	"Level test: WARNING\n");
	printk(KERN_NOTICE	"Level test: NOCICE\n");
	printk(KERN_INFO	"Level test: INFO\n");
	printk(KERN_DEBUG	"Level test: DEBUG.\n");

	// Set log level for default console (ttyS0):
	// # echo 7 > /proc/sys/kernel/printk
	// # cat /proc/sys/kernel/printk
	//    (First number is the console log level.)
	//
	// via UBOOT:
	// - append to cmdline: loglevel=#
	// U-BOOT# set bootargs ${bootargs} loglevel=3
	//
	// View with...
	// > dmesg
}


static int __init testdriver_init(void)
{
	printk(KERN_INFO "----> My demo_printk's init().\n");
	testPrintk();
	return 0;
}

static void __exit testdriver_exit(void)
{
	printk(KERN_INFO "<---- My demo_printk driver's exit().\n");
}

// Link our init/exit functions into the kernel's code.
module_init(testdriver_init);
module_exit(testdriver_exit);

// Information about this module:
MODULE_AUTHOR("Brian Fraser");
MODULE_DESCRIPTION("Driver to show use of printk().");
MODULE_LICENSE("GPL");		// Important to leave as GPL.
