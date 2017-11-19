/*
 * echo.c
 * - Simple echo driver: what is written to it is echoed on read.
 * - Demonstrates FIFO in kernel.
 *      Author: Brian Fraser
 */

// DEMO (2 command prompts):
//    for((;;)) do cat /dev/echo; sleep 0.1; done;
//    echo 'hello world!' > /dev/echo
#include <linux/module.h>
#include <linux/miscdevice.h>		// for misc-driver calls.
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>

#define echo_DEVICE_FILE  "echo"


/**************************************************************
 * FIFO Support
 *************************************************************/
// Info on the interface:
//    https://www.kernel.org/doc/htmldocs/kernel-api/kfifo.html#idp10765104
// Good example:
//    http://lxr.free-electrons.com/source/samples/kfifo/bytestream-example.c
#include <linux/kfifo.h>
#define FIFO_SIZE 256	// Must be a power of 2.
static DECLARE_KFIFO(echo_fifo, char, FIFO_SIZE);


/******************************************************
 * Callbacks
 ******************************************************/
static ssize_t echo_read(struct file *file,
		char *buf, size_t count, loff_t *ppos)
{
	// Pull all available data from fifo into user buffer
	int num_bytes_read = 0;
	if (kfifo_to_user(&echo_fifo, buf, count, &num_bytes_read)) {
		return -EFAULT;
	}

	// Can use kfifo_get() to pull out a single value to kernel:
	/*
	int val;
	if (!kfifo_get(&echo_fifo, &val)) {
		// fifo empty.... handle it some how
	}
	// now data is in val... do with it what you will.
	*/

	return num_bytes_read;  // # bytes actually read.
}

static ssize_t echo_write(struct file *file,
		const char *buff, size_t count, loff_t *ppos)
{
	int i;
	int copied;

	// Push data into fifo, one byte at a time (with delays)
	for (i = 0; i < count; i++) {
		// Demo how to insert to fifo directly from user-buffer
		if (kfifo_from_user(&echo_fifo, &buff[i], sizeof(buff[i]), &copied)) {
			return -EFAULT;
		}

		// Demo how to insert data from kernel-mode into fifo
		if (!kfifo_put(&echo_fifo, '_')) {
			// Fifo full
			return -EFAULT;
		}
		msleep(100);
	}
	// Return # bytes actually written.
	return count;
}


/******************************************************
 * Misc support
 ******************************************************/
// Callbacks:  (structure defined in /linux/fs.h)
struct file_operations echo_fops = {
	.owner    =  THIS_MODULE,
	.read     =  echo_read,
	.write    =  echo_write,
};

// Character Device info for the Kernel:
static struct miscdevice echo_miscdevice = {
		.minor    = MISC_DYNAMIC_MINOR,           // Let the system assign one.
		.name     = echo_DEVICE_FILE,             // /dev/.... file.
		.fops     = &echo_fops                    // Callback functions.
};


/******************************************************
 * Driver initialization and exit:
 ******************************************************/
static int __init echo_init(void)
{
	// Initialize the FIFO.
	INIT_KFIFO(echo_fifo);

	// Register as a misc driver:
	return misc_register(&echo_miscdevice);
}

static void __exit echo_exit(void)
{
	// Unregister misc driver
	misc_deregister(&echo_miscdevice);
}

module_init(echo_init);
module_exit(echo_exit);

MODULE_AUTHOR("Brian Fraser");
MODULE_DESCRIPTION("A simple KFIFO demo app for echo.");
MODULE_LICENSE("GPL");
