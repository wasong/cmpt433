#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdint.h>

#define LINUX_BUS1 "/dev/i2c-1"
#define DEVICE_ADDRESS 0x1C

int initI2cBus(char* bus, int address)
{
	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0){
		printf("I@C: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is: ");
		exit(1);
	}
	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if(result < 0){
		perror("I2C: Unable to set I2C device to slave address.");
		exit(1);
	}
	return i2cFileDesc;
}

int main()
{
	int i2cFileDesc = initI2cBus(LINUX_BUS1, DEVICE_ADDRESS);
	
	return 0;
}