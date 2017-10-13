#include "fileHandler.h"
#include "sleep.h"
#include "reader.h"
#include "display.h"
#include "I2C.h"
#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run() {
	initDisplay();
	int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);

	// turn on displays
	writeI2cReg(i2cFileDesc, REG_DIRA, 0x00);
	writeI2cReg(i2cFileDesc, REG_DIRB, 0x00);

	// clear
	writeI2cReg(i2cFileDesc, REG_OUTA, 0x00);
	writeI2cReg(i2cFileDesc, REG_OUTB, 0x00);

	// int counter;
	while (1) {
		// for (counter = 0x00; counter <= 0xFF; counter++) {
		hideLeft();
		showRight();
		writeI2cReg(i2cFileDesc, REG_OUTA, NINE_L);
		writeI2cReg(i2cFileDesc, REG_OUTB, NINE_U);
		slip(0, 5000000);
		showLeft();
		hideRight();
		writeI2cReg(i2cFileDesc, REG_OUTA, TWO_L);
		writeI2cReg(i2cFileDesc, REG_OUTB, TWO_U);
		slip(0, 5000000);
		// }
		int arraySz = getArraySize();
		printf("Size: %d\n", arraySz);
	}

	// Cleanup I2C access;
	close(i2cFileDesc);
}

