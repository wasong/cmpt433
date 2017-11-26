/*
 * demo_seqfile_procdrv.c
 * Demonstrates how to use a seqfile (sequential file) to simplify code
 *      Author: Brian Fraser
 */
#include <linux/module.h>

#define DEVICE_NAME  "demoseqfile"

/******************************************************
 * /proc Interface via a Sequential File
 ******************************************************/
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

// Generate the content to show to the user:
#define NUM_VALUES 1024
static int my_proc_show(struct seq_file *file, void *extra)
{
	int i = 0;
	// That this can generate too much content for one buffer
	// when application tries to do a read file-operation.
	// Because it's hard to split up, use the sequential file
	// to handle that for us!

	seq_printf(file, "Using a Sequential File:\n");
	seq_printf(file, "====================\n");
	seq_printf(file, "Printing %d numbers:\n", NUM_VALUES);

	for (i = 0; i < NUM_VALUES; i++) {
		seq_printf(file, "0x%016x,", i);
		if (i % 4 == 0) {
			seq_printf(file, "\n");
		}
	}
	seq_printf(file, "\nDone\n");
	return 0;
}

static int my_open_proc_info(struct inode *inode, struct file *file)
{
	// Setup the sequential-file code to call my_proc_show
	// to generate content
	return single_open(file, my_proc_show, NULL);
}

// Setup callbacks to all the functions for /proc.
static const struct file_operations proc_fops = {
    .owner	= THIS_MODULE,
    .open	= my_open_proc_info,
    .read	= seq_read,             // Handled by sequential file
    .llseek	= seq_lseek,            // Handled by sequential file
    .release= single_release,       // Handled by sequential file
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
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Brian fraser");
MODULE_DESCRIPTION("A simple test driver");
MODULE_LICENSE("GPL");
