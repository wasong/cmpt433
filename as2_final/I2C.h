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

#define ZERO_L  0xA1
#define ZERO_U  0x86
#define ONE_L   0x80
#define ONE_U   0x02
#define TWO_L   0x31
#define TWO_U   0x0E
#define THREE_L 0xB0
#define THREE_U 0x0E
#define FOUR_L  0x90
#define FOUR_U  0x8A
#define FIVE_L  0xB0
#define FIVE_U  0x8C
#define SIX_L   0xB1
#define SIX_U   0x8C
#define SEVEN_L 0x80
#define SEVEN_U 0x06
#define EIGHT_L 0xB1
#define EIGHT_U 0x8E
#define NINE_L  0x90
#define NINE_U  0x8E

// public functions
int initI2C();
void endI2C();

void writeNumber(int i2cFileDesc, int number);

int initI2cBus(char * bus, int address);
unsigned char readI2cReg(int i2cFileDesc, unsigned char regAdd);
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);

#endif // I2C_H_
