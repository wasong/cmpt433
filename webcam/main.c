/********************

Author: Mohamed Yahye
Date: Nov 25 ,2017
Purpose: Runs all threads


********************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "grabber.h"
#include "keypad.h"
#include "door_sensor.h"
#include "audioMixer.h"
#include "server.h"

int main(){

  AudioMixer_init();
  server_init()
  webcam_init();
  Keypad_init();
  Door_init();

  char code[] = "123456";
  Keypad_setCode(6, code);
	
  webcam_join();
  server_join();

  return 0;
}
