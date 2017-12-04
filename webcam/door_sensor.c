#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "door_sensor.h"
#include "keypad.h"

#define _250MS_IN_NS 250000000L
#define _30S_IN_NS 30000000000L
#define BUFFER_SIZE 256
#define GPIO_EXPORT "/sys/class/gpio/export"
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"
#define GPIO_IN "/sys/class/gpio/gpio68/value"
#define GPIO_IN_DIR "/sys/class/gpio/gpio68/direction"

static int run = 0;
static pthread_t door_id;
static const int _30s = (int) (_30S_IN_NS / _250MS_IN_NS);
static int open = 0;

void *doorReader();
int getVal();

void Door_init()
{
  FILE *file = fopen(GPIO_EXPORT, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO export file!");
    return;
  }
  fprintf(file, "%s", "68");
  fclose(file);
  
  file = fopen(GPIO_IN_DIR, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO 68 dir file!");
    return;
  }
  fprintf(file, "%s", "in");
  fclose(file);

  run = 1;
  pthread_create(&door_id, NULL, doorReader, NULL);
}

void Door_unInit()
{
  run = 0;
  pthread_join(door_id, NULL);

  FILE *file = fopen(GPIO_UNEXPORT, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO unexport file!");
    return;
  }
  fprintf(file, "%s", "68");
  fclose(file);
}

int Door_isOpen()
{
  return open;
}

void *doorReader()
{
  struct timespec delay;
  delay.tv_sec = 0;
  delay.tv_nsec = _250MS_IN_NS;

  int value = 0;
  int count = 0;
  
  while (run) {
    nanosleep(&delay, NULL);
    value = getVal();
    
    if (value == 0) {
      //printf("DOOR: OPEN!\n");
      open = 1;

      if (!Keypad_getCodeEntered()) {
	++count;
	if (count >= _30s) {
	  // activate the alarm
	  Keypad_setAlarm(1);
	}
      }
    } else {
      //printf("DOOR: CLOSED!\n");
      open = 0;
    }
    
  }

  return NULL;
}

int getVal()
{
  FILE *file = fopen(GPIO_IN, "r");
  if (file == NULL) {
    perror("Couldn't open GPIO value file!");
    return -1;
  }

  char buffer[BUFFER_SIZE];
  fgets(buffer, BUFFER_SIZE, file);
  fclose(file);

  if (buffer[0] == '0')
    return 0;
  else
    return 1;
  
}
