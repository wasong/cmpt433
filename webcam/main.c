/********************

Author: Mohamed Yahye
Date: Nov 25 ,2017
Purpose: Runs all threads


********************/
#include <stdlib.h>
#include <stdio.h>
#include "grabber.h"
#include "wave_player.h"
#include "server.h"

int main(){
	
	webcam_init();
	sound_init();
	server_init();
	
	webcam_join();
	sound_join();
	server_join();
	
	return 0;
}