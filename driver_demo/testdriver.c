// Example test driver:
#include <linux/module.h>

static int __init testdriver_init(void)
{
	printk(KERN_INFO "----> My test driver init()\n");
	return 0;
}
static void __exit testdriver_exit(void)
{
	printk(KERN_INFO "<---- My test driver exit().\n");
}

// Link our init/exit functions into the kernel's code.
module_init(testdriver_init);
module_exit(testdriver_exit);

// Information about this module:
MODULE_AUTHOR("Andrew");
MODULE_DESCRIPTION("A simple test driver");
MODULE_LICENSE("GPL"); // Important to leave as GPL.
