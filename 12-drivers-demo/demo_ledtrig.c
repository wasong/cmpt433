/*
 * demo_ledtrig.c
 * - Demonstrate how to flash an LED using a custom trigger.
 *      Author: Brian Fraser
 */
#include <linux/module.h>
#include <linux/miscdevice.h>		// for misc-driver calls.
#include <linux/fs.h>
#include <linux/delay.h>
//#error Are we building this?

#define MY_DEVICE_FILE  "demo_ledtrig"

/******************************************************
 * LED
 ******************************************************/
#include <linux/leds.h>

DEFINE_LED_TRIGGER(ledtrig_demo);

#define LED_ON_TIME_ms 100
#define LED_OFF_TIME_ms 900

static void my_led_blink(void)
{
	led_trigger_event(ledtrig_demo, LED_FULL);
	msleep(LED_ON_TIME_ms);
	led_trigger_event(ledtrig_demo, LED_OFF);
	msleep(LED_OFF_TIME_ms);
}

static void led_register(void)
{
	// Setup the trigger's name:
	led_trigger_register_simple("demo", &ledtrig_demo);
}

static void led_unregister(void)
{
	// Cleanup
	led_trigger_unregister_simple(ledtrig_demo);
}


/******************************************************
 * Callbacks
 ******************************************************/
static ssize_t my_write(struct file* file, const char *buff,
		size_t count, loff_t* ppos)
{
	int i;
	printk(KERN_INFO "demo_ledtrig: Flashing %d times for string.\n", count);

	// Blink once per character (-1 to skip end null)
	for (i = 0; i < count-1; i++) {
		my_led_blink();
	}

	// Return # bytes actually written.
	return count;
}


/******************************************************
 * Misc support
 ******************************************************/
// Callbacks:  (structure defined in <kernel>/include/linux/fs.h)
struct file_operations my_fops = {
	.owner    =  THIS_MODULE,
	.write    =  my_write,
};

// Character Device info for the Kernel:
static struct miscdevice my_miscdevice = {
		.minor    = MISC_DYNAMIC_MINOR,         // Let the system assign one.
		.name     = MY_DEVICE_FILE,             // /dev/.... file.
		.fops     = &my_fops                    // Callback functions.
};


/******************************************************
 * Driver initialization and exit:
 ******************************************************/
static int __init my_init(void)
{
	int ret;
	printk(KERN_INFO "----> demo_misc driver init(): file /dev/%s.\n", MY_DEVICE_FILE);

	// Register as a misc driver:
	ret = misc_register(&my_miscdevice);

	// LED:
	led_register();

	return ret;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "<---- demo_misc driver exit().\n");

	// Unregister misc driver
	misc_deregister(&my_miscdevice);

	// LED:
	led_unregister();
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Brian Fraser");
MODULE_DESCRIPTION("A simple test driver");
MODULE_LICENSE("GPL");
