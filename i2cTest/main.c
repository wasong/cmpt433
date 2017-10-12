#include "I2C.h"
#include "sleep.h"
#include "display.h"
#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Drive display (assumes GPIO #61 and #44 are output and 1)\n");
	initDisplay();
	int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);

	writeI2cReg(i2cFileDesc, REG_DIRA, 0x00);
	writeI2cReg(i2cFileDesc, REG_DIRB, 0x00);

	// clear
	writeI2cReg(i2cFileDesc, REG_OUTA, 0x00);
	writeI2cReg(i2cFileDesc, REG_OUTB, 0x00);

	int counter;
	for (counter = 0x00; counter <= 0xFF; counter++) {
		printf("counter: %x\n", counter);
		writeI2cReg(i2cFileDesc, REG_OUTA, counter);
		writeI2cReg(i2cFileDesc, REG_OUTB, counter);
		slip(1, 0);
	}
		

	// Read a register:
	unsigned char regVal = readI2cReg(i2cFileDesc, REG_OUTA);
	printf("Reg OUT-A = 0x%02x\n", regVal);

	// Cleanup I2C access;
	close(i2cFileDesc);

	return 0;
}
