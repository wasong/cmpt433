// Example test driver:
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/kfifo.h>
#include <linux/leds.h>

#define DEVICE_FILE "morse_code"
#define DOTTIME 200

// driver parameter dot time
static int dottime = DOTTIME;
module_param(dottime, int, S_IRUGO);
MODULE_PARM_DESC(dottime, "Dot time in ms");

// LED and KFIFO
#define FIFO_SIZE 256
#define BUFFER_SIZE 1024

DEFINE_LED_TRIGGER(led_trigger);
static void led_register(void) {
  led_trigger_register_simple("morse-code", &led_trigger);
}

static void led_unregister(void) {
  led_trigger_unregister_simple(led_trigger);
}

#define UPPER_HIGH_BOUND 65 // A
#define UPPER_LOW_BOUND 90 // Z
#define LOWER_HIGH_BOUND 97 // a
#define LOWER_LOW_BOUND 122 // z

// bitwise values
unsigned short BIT_MASK = 0x8000;
int BIT_SHIFT = 15;
int BIT_SIZE = 16; // 4 byte char

static DECLARE_KFIFO(echo_fifo, char, FIFO_SIZE);

// morse code array
static unsigned short morsecode_codes[] = {
		0xB800,	// A 1011 1
		0xEA80,	// B 1110 1010 1
		0xEBA0,	// C 1110 1011 101
		0xEA00,	// D 1110 101
		0x8000,	// E 1
		0xAE80,	// F 1010 1110 1
		0xEE80,	// G 1110 1110 1
		0xAA00,	// H 1010 101
		0xA000,	// I 101
		0xBBB8,	// J 1011 1011 1011 1
		0xEB80,	// K 1110 1011 1
		0xBA80,	// L 1011 1010 1
		0xEE00,	// M 1110 111
		0xE800,	// N 1110 1
		0xEEE0,	// O 1110 1110 111
		0xBBA0,	// P 1011 1011 101
		0xEEB8,	// Q 1110 1110 1011 1
		0xBA00,	// R 1011 101
		0xA800,	// S 1010 1
		0xE000,	// T 111
		0xAE00,	// U 1010 111
		0xAB80,	// V 1010 1011 1
		0xBB80,	// W 1011 1011 1
		0xEAE0,	// X 1110 1010 111
		0xEBB8,	// Y 1110 1011 1011 1
		0xEEA0	// Z 1110 1110 101
};

/******************************************************
 * Callbacks
 ******************************************************/

// returns hex value from morsecode array
static unsigned short process_char(char ch) {
	if (ch == ' ') return 1;

	if (ch >= UPPER_HIGH_BOUND && ch <= UPPER_LOW_BOUND) return morsecode_codes[ch - UPPER_HIGH_BOUND];
	if (ch >= LOWER_HIGH_BOUND && ch <= LOWER_LOW_BOUND) return morsecode_codes[ch - LOWER_HIGH_BOUND];
 return 0; // handles non space or alphanumeric chars
}

// bit shifting operations and flashes LED appropriately
static void process_hex(unsigned short hex) {
	int i;
 int max_dots = 3;
 int dash_counter = 0;
 int sleep_time = dottime;

 if (hex == 0) return;

 if (hex == 1) {
  // TODO: handle writing 3 spaces to kfifo
  if (!kfifo_put(&echo_fifo, ' ')) return -EFAULT;
  if (!kfifo_put(&echo_fifo, ' ')) return -EFAULT;
  if (!kfifo_put(&echo_fifo, ' ')) return -EFAULT;

  led_trigger_event(led_trigger, LED_OFF); // turn off LED

  msleep(dottime * 7); // spaces are 7 dottimes
  return;
 }

 for (i = 0; i < BIT_SIZE; i++) {
  unsigned short mask = BIT_MASK >> i; // new mask
  unsigned short maskedBits = hex & mask;
  unsigned short shiftedBits = maskedBits >> (BIT_SHIFT - i);

  // handle dot and dash count
  if (shiftedBits == 1) { // handle unknown dot or dash
   dash_counter++; // increment counter

   if (dash_counter == max_dots) { // if 3 dots
    // flash dash
    if (!kfifo_put(&echo_fifo, '-')) return -EFAULT;

    led_trigger_event(led_trigger, LED_FULL); // turn on led
    sleep_time = dottime * 3; // flash for 3 dot times
    dash_counter = 0; // reset
   }
  } else {
   // handle a dot
   if (dash_counter == 1) {
    if (!kfifo_put(&echo_fifo, '.')) return -EFAULT;
    led_trigger_event(led_trigger, LED_FULL); // turn on led
    sleep_time = dottime;
    dash_counter = 0;
   }
  }
  msleep(sleep_time); // sleep for dot/dash

  // inbetween dots/dashes (1 dot time sleep with LED off)
  led_trigger_event(led_trigger, LED_OFF); // turn off LED
  sleep_time = dottime;
  msleep(sleep_time);
 }
 msleep(sleep_time * 2); // inbetween letters
}

static ssize_t my_read(struct file *file,
		char *buff, size_t count, loff_t *ppos)
{
	int bytes_read = 0;

 if (kfifo_to_user(&echo_fifo, buff, count, &bytes_read)) {
  printk(KERN_ERR "Unable to write to buffer.");
  return -EFAULT;
 }
	return bytes_read;  // # bytes actually read.
}

static ssize_t my_write(struct file *file,
		const char *buff, size_t count, loff_t *ppos)
{
 unsigned short morseHexValue;
	int buff_idx = 0;
	char ch;

	printk(KERN_INFO "demo_miscdrv: In my_write()\n");

	// Find min character
	for (buff_idx = 0; buff_idx < count; buff_idx++) {
		// Get the character
		if (copy_from_user(&ch, &buff[buff_idx], sizeof(ch))) {
			return -EFAULT;
		}

		// Process the character
		morseHexValue = process_char(ch);
		process_hex(morseHexValue);
	}

 if (!kfifo_put(&echo_fifo, '\n')) return -EFAULT;

	// Return # bytes actually written.
	*ppos += count;
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
		.name     = DEVICE_FILE,             // /dev/.... file.
		.fops     = &my_fops                    // Callback functions.
};

static int __init morsecode_init(void)
{
	int ret;
	printk(KERN_INFO "----> My morse driver init()\n");

 // dottime range check
 if (dottime < 1 || dottime > 2000) {
  printk(KERN_ERR "dottime out of range; must be between 1 - 2000.\n");
  dottime = DOTTIME;
 }
 
 INIT_KFIFO(echo_fifo);
	ret = misc_register(&my_miscdevice);
 led_register();

 return ret;
}

static void __exit morsecode_exit(void)
{
	printk(KERN_INFO "<---- My morse driver exit().\n");

	// unregister
	misc_deregister(&my_miscdevice);
 led_unregister();
}

// Link our init/exit functions into the kernel's code.
module_init(morsecode_init);
module_exit(morsecode_exit);

// Information about this module:
MODULE_AUTHOR("Vaan and Andrew");
MODULE_DESCRIPTION("Morsecode misc driver");
MODULE_LICENSE("GPL"); // Important to leave as GPL.
