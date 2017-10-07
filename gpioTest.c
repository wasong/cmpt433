#include <stdlib.h>
#include <stdio.h>

void exportGPIOFile(char* fileName, int pin) {
	printf("Called %s, %d", fileName, pin);
	FILE *pfile = fopen(fileName, "w");

	if (pfile == NULL) {
		printf("ERROR: Unable to open the file.\n");
		exit(1);
	}

	fprintf(pfile, "%d", pin);

	fclose(pfile);
}

int main() {
	exportGPIOFile("/sys/class/gpio/export", 30);
	return 0;
}
