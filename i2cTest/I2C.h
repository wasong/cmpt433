#ifndef I2C_H_
#define I2C_H_

#define I2C_DEVICE_ADDRESS 0x20
#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"

#define REG_DIRA 0x00
#define REG_DIRB 0x01
#define REG_OUTA 0x14
#define REG_OUTB 0x15

// public functions
int initI2cBus(char * bus, int address);
unsigned char readI2cReg(int i2cFileDesc, unsigned char regAdd);
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);

#endif // I2C_H_
