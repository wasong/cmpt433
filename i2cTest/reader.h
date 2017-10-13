// reader.h
// represents the Potentiometer reader

#ifndef READER_H_
#define READER_H_

#define A2D_FILE_VOLTAGE0 "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define A2D_VOLTAGE_REF_V 1.8
#define A2D_MAX_READING 4095

#define PIECEWISE_SZ 10

const int PIECEWISE_ARR_SZ[10];
const int PIECEWISE_POT[10];

int getArraySize();

#endif
