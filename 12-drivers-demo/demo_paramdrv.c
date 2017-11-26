/*
 * demo_paramdrv.c
 *
 *  Created on: Oct 15, 2011
 *      Author: Brian Fraser
 */
#include <linux/module.h>
#include <linux/miscdevice.h>		// for misc-driver calls.
#include <linux/fs.h>
#include <asm/uaccess.h>

//#error Are we building this?



#define DEVICE_NAME  "demoparam"

/******************************************************
 * Parameter
 ******************************************************/
#define DEFAULT_FAV_NUM       42
static int myfavnumber = DEFAULT_FAV_NUM;

// Declare the variable as a parameter.
//   S_IRUGO makes it's /sys/module node readable.
//   # cat /sys/module/demo_paramdrv/parameters/myfavnumber
// Loading:
//   # modinfo demo_paramdrv.ko
//   # insmod demo_paramdrv.ko myfavnumber=932
module_param(myfavnumber, int, S_IRUGO);
MODULE_PARM_DESC(myfavnumber, " My favourite number!");


/******************************************************
 * File Operation Callbacks
 ******************************************************/
#define PRINT_BUFFER_SIZE 1024
static char print_buffer[PRINT_BUFFER_SIZE];

static ssize_t my_read(struct file *file,
		char *buf, size_t count, loff_t *ppos)
{
	int read_offset = (int) *ppos;
	int bytes_read = 0;
	int length = 0;

	// Generate the data:
	// Note that two string literals back-to-back are merged by the compiler.
	length = snprintf(print_buffer, PRINT_BUFFER_SIZE,
			"Fav# = %d\n,",
			myfavnumber);

	// Copy generate text into the user's buffer
	// (size limited by how much data as we have, and size of the user's buffer)
	bytes_read = length - read_offset;
	if (bytes_read > count) {
		bytes_read = count;
	}
	if (copy_to_user(buf, print_buffer + read_offset, bytes_read)) {
		return -EFAULT;
	}

	// Return what we read
	*ppos += bytes_read;
	return bytes_read;
}


/******************************************************
 * Misc support
 ******************************************************/
// Callbacks:  (structure defined in /linux/fs.h)
struct file_operations my_fops = {
	.owner    =  THIS_MODULE,
	.read     =  my_read,
};

// Character Device info for the Kernel:
static struct miscdevice my_miscdevice = {
		.minor    = MISC_DYNAMIC_MINOR,         // Let the system assign one.
		.name     = DEVICE_NAME,                // /dev/.... file.
		.fops     = &my_fops                    // Callback functions.
};


/******************************************************
 * Driver initialization and exit:
 ******************************************************/
static int __init my_init(void)
{
	int ret;
	printk(KERN_INFO "----> Brian's parameter driver init()\n");

	// Register as a misc driver:
	ret = misc_register(&my_miscdevice);

	return ret;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "----> Brian's parameter driver exit().\n");

	// Unregister misc driver
	misc_deregister(&my_miscdevice);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Brian fraser");
MODULE_DESCRIPTION("A simple test driver");
MODULE_LICENSE("GPL");
