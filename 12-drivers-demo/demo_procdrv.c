/*
 * demo_procdrv.c
 *      Author: Brian Fraser
 */
#include <linux/module.h>
#include <asm/uaccess.h>


#define DEVICE_NAME  "demoproc"

/******************************************************
 * /proc Interface
 ******************************************************/
#include <linux/proc_fs.h>			// /proc

#define PRINT_BUFFER_SIZE 1024
static char print_buffer[PRINT_BUFFER_SIZE];

/* Read information from this /proc entry:
 * 	returns: Number of bytes written to page.
 */
static int my_read_proc_info(struct file *file, char *buf, size_t count, loff_t *offp)
{
	int read_offset = (int) *offp;
	int bytes_read = 0;
	int length = 0;

	// Generate the data:
	// Note that two string literals back-to-back are merged by the compiler.
	length = snprintf(print_buffer, PRINT_BUFFER_SIZE,
				"Da test driver info:\n"
				"====================\n"
				"Fav Number:       %d\n"
				"# Pink Elephants: %d\n"
				"Greeting:         %s\n"
				"\n",

				42, 0, "Hello world!"
			);

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
	*offp += bytes_read;
	return bytes_read;
}

// Setup callbacks to all the functions for proc.
// (an also use write, close, ....)
struct file_operations proc_fops = {
		.owner= THIS_MODULE,
		.read = my_read_proc_info
};

/******************************************************
 * Driver initialization and exit:
 ******************************************************/
static int __init my_init(void)
{
	printk(KERN_INFO "----> Brian's proc driver init()\n");

	// Register proc:
	proc_create(
			DEVICE_NAME,           // name of /proc/... entry.
			0,                     // Mode (r/w)
			NULL,                  // Parent (none)
			&proc_fops             // file_operations struct
			);

	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "----> Brian's proc driver exit().\n");

	// Unregister /proc
	remove_proc_entry(DEVICE_NAME, NULL);

//	// Unregister misc driver
//	misc_deregister(&my_miscdevice);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Brian fraser");
MODULE_DESCRIPTION("A simple test driver");
MODULE_LICENSE("GPL");
