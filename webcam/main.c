/********************

Author: Mohamed Yahye
Date: Nov 25 ,2017
Purpose: Runs all threads


********************/
#include <stdlib.h>
#include <stdio.h>
#include "grabber.h"


int main(){
	
	webcam_init();
	//keypad_init();

	webcam_join();
	//keypad_join();
	return 0;
}