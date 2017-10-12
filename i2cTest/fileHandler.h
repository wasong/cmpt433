#ifndef FILE_H_
#define FILE_H_

#define EXPORT_FILE "/sys/class/gpio/export"
#include <stdio.h>

FILE* openFile(char* fileName, char* type);
void closeFile(FILE* file);
void exportGPIOPin(int pin);
void writeToFile(char* fileName, char* value);

#endif // FILE_H_
