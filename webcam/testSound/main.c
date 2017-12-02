/********************

Author: Mohamed Yahye
Date: Nov 25 ,2017
Purpose: Runs all threads


********************/
#include <stdlib.h>
#include <stdio.h>
#include "wave_player.h"


int main(){
	
	sound_init();
	//keypad_init();

	sound_join();
	//keypad_join();
	return 0;
}