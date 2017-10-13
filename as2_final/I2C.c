#include "I2C.h"
#include "display.h"
#include "sleep.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

int initI2C() {
	int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);

	// turn on displays
	writeI2cReg(i2cFileDesc, REG_DIRA, 0x00);
	writeI2cReg(i2cFileDesc, REG_DIRB, 0x00);

	// clear
	writeI2cReg(i2cFileDesc, REG_OUTA, 0x00);
	writeI2cReg(i2cFileDesc, REG_OUTB, 0x00);
	
	return i2cFileDesc;
}

void endI2C(int i2cFileDesc) {
	close(i2cFileDesc);
}

int* getNumbers (int number) {
	int* nums = (int*) malloc(2 * sizeof(int));
	switch(number) {
		case 0:
			nums[0] = 0xA1;
			nums[1] = 0x86;
      			break;
		case 1:
			nums[0] = 0x80;
			nums[1] = 0x02;
      			break;
		case 2:
			nums[0] = 0x31;
			nums[1] = 0x0E;
      			break;
		case 3:
			nums[0] = 0xB0;
			nums[1] = 0x0E;
      			break;
		case 4:
			nums[0] = 0x90;
			nums[1] = 0x8A;
      			break;
		case 5:
			nums[0] = 0xB0;
			nums[1] = 0x8C;
      			break;
		case 6:
			nums[0] = 0xB1;
			nums[1] = 0x8C;
      			break;
		case 7:
			nums[0] = 0x80;
			nums[1] = 0x06;
      			break;
		case 8:
			nums[0] = 0xB1;
			nums[1] = 0x8E;
      			break;
		case 9:
			nums[0] = 0x90;
			nums[1] = 0x8E;
      			break;
		default:
			nums[0] = 0xA1;
			nums[1] = 0x86;
	}
	return nums;
}

void writeNumber(int i2cFileDesc, int number) {
	int newNum = number;
	if (newNum > 99) newNum = 99;

	int leftNumber = (int) floor(newNum / 10);
	int rightNumber = newNum % 10;

	int* leftDigit = getNumbers(leftNumber);
	int* rightDigit = getNumbers(rightNumber);
	
	showRight();
	writeI2cReg(i2cFileDesc, REG_OUTA, rightDigit[0]);
	writeI2cReg(i2cFileDesc, REG_OUTB, rightDigit[1]);
	slip(0, 5000000);

	showLeft();
	writeI2cReg(i2cFileDesc, REG_OUTA, leftDigit[0]);
	writeI2cReg(i2cFileDesc, REG_OUTB, leftDigit[1]);
	slip(0, 5000000);

	free(leftDigit);
	free(rightDigit);
}

int initI2cBus(char * bus, int address) {
	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is:");
		exit(1);
	}

	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("I2C: Unable to set I2C device to slave address.");
		exit(1);
	}

	return i2cFileDesc;
}

unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr) {
	// To read a register, must first write the address
	int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
	if (res != sizeof(regAddr)) {
		perror("I2C: Unable to write to i2c register.");
		exit(1);
	}

	// Now read the value and return it
	char value = 0;
	res = read(i2cFileDesc, &value, sizeof(value));
	if (res != sizeof(value)) {
		perror("I2C: Unable to read from i2c register");
		exit(1);
	}
	return value;
}

void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value) {
	unsigned char buff[2];
	buff[0] = regAddr;
	buff[1] = value;

	int res = write(i2cFileDesc, buff, 2);
	if (res != 2) {
		perror("I2C: Unable to write i2c register.");
		exit(1);
	}
}
