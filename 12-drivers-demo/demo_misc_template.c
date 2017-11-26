/*
 * demo_miscdrv.c
 * - Demonstrate how to use a misc driver to easily create a file system link
 *      Author: Brian Fraser
 */
#include <linux/module.h>
#include <linux/miscdevice.h>		// for misc-driver calls.
#include <linux/fs.h>
#include <linux/delay.h>
//#error Are we building this?

#define MY_DEVICE_FILE  "my_demo_misc"


/******************************************************
 * Callbacks
 ******************************************************/
static int my_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "demo_miscdrv: In my_open()\n");
	return 0;  // Success
}

static int my_close(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "demo_miscdrv: In my_close()\n");
	return 0;  // Success
}

static ssize_t my_read(struct file *file,
		char *buff,	size_t count, loff_t *ppos)
{
	printk(KERN_INFO "demo_miscdrv: In my_read()\n");
	return 0;  // # bytes actually read.
}

static ssize_t my_write(struct file *file,
		const char *buff, size_t count, loff_t *ppos)
{
	printk(KERN_INFO "demo_miscdrv: In my_write()\n");
	// Return # bytes actually written.
	// Return count here just to make it not call us again!
	return count;
}

static long my_unlocked_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "demo_miscdrv: In my_unlocked_ioctl()\n");
	return 0;  // Success
}



/******************************************************
 * Misc support
 ******************************************************/
// Callbacks:  (structure defined in /linux/fs.h)
struct file_operations my_fops = {
	.owner    =  THIS_MODULE,
	.open     =  my_open,
	.release  =  my_close,
	.read     =  my_read,
	.write    =  my_write,
	.unlocked_ioctl =  my_unlocked_ioctl
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
MODULE_DESCRIPTION("A simple test driver");
MODULE_LICENSE("GPL");
