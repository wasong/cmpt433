#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdint.h>

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x1C


int initI2cBus(char* bus, int address)
{
	// Create i2c bus
	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is");
		exit(1);
	}

	// Get i2c device, MMA84520Q I2C address is 0x1C(28)
	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("I2C: Unable to set I2C device to slave address.");
		exit(1);
	}

	return i2cFileDesc;
}


int main() 
{

	int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1,I2C_DEVICE_ADDRESS);

	// Select mode register(0x2A)
	// Standby mode(0x00)
	char config[2] = {0};
	config[0] = 0x2A;
	config[1] = 0x00;
	write(i2cFileDesc, config, 2);

	// Select mode register(0x2A)
	// Active mode(0x01)
	config[0] = 0x2A;
	config[1] = 0x01;
	write(i2cFileDesc, config, 2);
	
	// Select configuration register(0x0E)
	// Set range to +/- 2g(0x00)
	config[0] = 0x0E;
	config[1] = 0x00;
	write(i2cFileDesc, config, 2);
	sleep(0.5);

	// Read 7 bytes of data(0x00)
	// staus, xAccl msb, xAccl lsb, yAccl msb, yAccl lsb, zAccl msb, zAccl lsb
	char reg[1] = {0x00};
	write(i2cFileDesc, reg, 1);
	char data[7] = {0};
	if(read(i2cFileDesc, data, 7) != 7)
	{
		printf("Error : Input/Output error \n");
	}
	else
	{
		// Convert the data to 12-bits
		int16_t xAccl = (data[1] << 8) | (data[2]);
		// if(xAccl > 2047)
		// {
		// 	xAccl -= 4096;
		// }

		int16_t yAccl = (data[3] << 8) | (data[4]);
		// if(yAccl > 2047)
		// {
		// 	yAccl -= 4096;
		// }

		int16_t zAccl = (data[5] << 8) | (data[6]);
		// if(zAccl > 2047)
		// {
		// 	zAccl -= 4096;
		// }

		// Output data to screen
		printf("Acceleration in X-Axis : %d \n", xAccl);
		printf("Acceleration in Y-Axis : %d \n", yAccl);
		printf("Acceleration in Z-Axis : %d \n", zAccl/(zAccl - 1));
	}

	return 0;
}