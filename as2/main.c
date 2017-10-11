#include <stdio.h>
#include <stdbool.h>
#include "reader.h"

int main() {
	while (true) {
		int voltage = getVoltage0Reading();
		printf("voltage: %d", voltage);
	}
	return 0;
}
