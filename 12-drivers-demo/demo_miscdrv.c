/*
 * demo_miscdrv.c
 * - Demonstrate how to use a misc driver to easily create a file system link
 *      Author: Brian Fraser
 */
#include <linux/module.h>
#include <linux/miscdevice.h>		// for misc-driver calls.
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>

//#error Are we building this?

#define MY_DEVICE_FILE  "my_demo_misc"

// Define the toy data:
#define START_CHAR 'A'
#define END_CHAR   'z'
#define DATA_SIZE  (END_CHAR - START_CHAR + 1)
static char data[DATA_SIZE];


/******************************************************
 * Initialization of Data Function
 ******************************************************/
static void initialize_data(void)
{
	int i = 0;
	for (i = 0; i < DATA_SIZE; i++) {
		data[i] = i + START_CHAR;
	}
}

/******************************************************
 * Callbacks
 ******************************************************/
static ssize_t my_read(struct file *file,
		char *buff, size_t count, loff_t *ppos)
{
	printk(KERN_INFO "demo_miscdrv::my_read(), buff size %d, f_pos %d\n",
			(int) count, (int) *ppos);

	// Give user back some data:
	// copy_to_user() returns number of characters not copied.
	if (copy_to_user(buff, "Hello world", 12)) {
		printk(KERN_ERR "Unable to write to buffer.");
		return -EFAULT;
	}

	// Note: Will never reach "end" of file.
	return 12;  // # bytes actually read.
}

static ssize_t my_write(struct file *file,
		const char *buff, size_t count, loff_t *ppos)
{
	int i = 0;

	printk(KERN_INFO "demo_miscdrv: In my_write(): ");

	for (i = 0; i < count; i++) {
		char ch;
		if (copy_from_user(&ch, &buff[i], sizeof(ch))) {
			return -EFAULT;
		}
		printk(KERN_INFO "%c", ch);
	}
	printk(KERN_INFO "\n");

	// Return # bytes actually written.
	return count;
}

/******************************************************
 * Misc support
 ******************************************************/
// Callbacks:  (structure defined in /linux/fs.h)
struct file_operations my_fops = {
	.owner    =  THIS_MODULE,
	.read     =  my_read,
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

	initialize_data();

	return ret;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "<---- demo_misc driver exit().\n");

	// Unregister misc driver
	misc_deregister(&my_miscdevice);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Brian Fraser");
MODULE_DESCRIPTION("Demo driver to return some ascii data, and reverse a string to printk.");
MODULE_LICENSE("GPL");
