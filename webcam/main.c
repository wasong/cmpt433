/********************

Author: Mohamed Yahye
Date: Nov 25 ,2017
Purpose: Runs all threads


********************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "grabber.h"
#include "keypad.h"
#include "door_sensor.h"
#include "audioMixer.h"
#include "server.h"

void test_keypad() {
  char code[64] = "";

  Keypad_setAlarmSound(1);
  
  strcpy(code, "1234");
  Keypad_setCode(4, code);

  sleep(45);
}

int main(){

  AudioMixer_init();
  server_init();
  Keypad_init();
  Door_init();

  test_keypad();
  
  //char code[] = "123456";
  //Keypad_setCode(6, code);
  
  server_join();
  Keypad_unInit();
  AudioMixer_cleanup();

  return 0;
}
