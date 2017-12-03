#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "keypad.h"
#include "audioMixer.h"
#include "grabber.h"

#define NS_DELAY 50000000L // 50ms in ns
#define _2S_IN_NS 2000000000L
#define BUFFER_SIZE 512
#define NUM_GPIO 12
#define GPIO_BASE_DIR "/sys/class/gpio/"
#define MAX_ERRORS 3
#define SOURCE_FILE "wave-files/Industrial-Alarm.wav"
//#define SOURCE_FILE "wave-files/drum.wav"

static int run = 0;
static pthread_t keypad_id;
static pthread_t alarm_id;
static const char *GPIO[] = { "88", "89", "86", "87", "10", "9", "8", "78", "76", "74", "72", "70" };
static const char KEYS[] = { '*', '7', '4', '1', '0', '8', '5', '2', '#', '9', '6', '3' };
static code_t code = { 0, NULL };
static const int _2s = (int) ((_2S_IN_NS) / NS_DELAY);
static int k_alarm = 0;
static int codeEntered = 0;

static void *keypad_reader();
static void *audio_player();
static char read_values(int *read, int *last, int *debounce);
static void copy_code(code_t *dest, const code_t *src);

// ========== Interface ==========

void Keypad_init()
{
  FILE *file;
  char buffer[BUFFER_SIZE] = "";

  // export GPIO pins
  for (int i = 0; i < NUM_GPIO; ++i) {
    file = fopen((GPIO_BASE_DIR "export"), "w");
    if (file == NULL)
      printf("Couldn't open GPIO export file!");
    fprintf(file, "%s", GPIO[i]);
    fclose(file);
  }

  // set directions as in
  for (int i = 0; i < NUM_GPIO; ++i) {
    strcpy(buffer, GPIO_BASE_DIR "gpio");
    strcat(buffer, GPIO[i]);
    strcat(buffer, "/direction");
    
    file = fopen(buffer, "w");
    if (file == NULL)
      printf("Couldn't set GPIO pin %s as input!", GPIO[i]);
    fprintf(file, "%s", "in");
    fclose(file);
  }

  codeEntered = 0;
  k_alarm = 0;
  run = 1;
  pthread_create(&keypad_id, NULL, keypad_reader, NULL);
  pthread_create(&alarm_id, NULL, audio_player, NULL);
}

void Keypad_unInit()
{
  run = 0;
  pthread_join(keypad_id, NULL);
  pthread_join(alarm_id, NULL);

  FILE *file;

  // unexport GPIO pins
  for (int i = 0; i < NUM_GPIO; ++i) {
    file = fopen((GPIO_BASE_DIR "unexport"), "w");
    if (file == NULL)
      printf("Couldn't open GPIO unexport file!");
    fprintf(file, "%s", GPIO[i]);
    fclose(file);
  }

  if (code.code != NULL)
    free(code.code);
}

void Keypad_setCode(int size, char *new_code)
{
  code_t new;
  new.size = size;
  new.code = new_code;

  copy_code(&code, &new);
}

code_t Keypad_getCode()
{
  return code;
}

void Keypad_setAlarm(int value)
{
  if (value == 0 || value == 1) {
    k_alarm = value;
  } else {
    perror("Invalid value given to Keypad_setAlarm()! (Must be either 0 or 1)");
    k_alarm = 0;
  }
}

int Keypad_getAlarm()
{
  return k_alarm;
}

int Keypad_getCodeEntered()
{
  return codeEntered;
}

// ========== Private functions ==========

static void *audio_player()
{
  wavedata_t pSound;
  AudioMixer_readWaveFileIntoMemory(SOURCE_FILE, &pSound);

  while (1) {
    //sleep(1);
    //printf("k_alarm = %d\n", k_alarm);
      if (!working) {
	AudioMixer_queueSound(&pSound);
	sleep(3);
      }
  }


  return NULL;
}

static void copy_code(code_t *dest, const code_t *src)
{
  if (src == NULL)
    return;

  dest->size = src->size;
  size_t new_size = sizeof(char) * (dest->size + 1);

  if (dest->code == NULL)
    dest->code = (char *) malloc(new_size);
  else
    dest->code = (char *) realloc(dest->code, new_size);

  memset(dest->code, 0, new_size);
  strcpy(dest->code, src->code);
}

static void *keypad_reader()
{
  /*struct timespec delay;
  delay.tv_sec = 0;
  delay.tv_nsec = NS_DELAY;
  
  int read[NUM_GPIO] = {0,0,0,0,0,0,0,0,0,0,0,0};
  int last[NUM_GPIO] = {0,0,0,0,0,0,0,0,0,0,0,0};
  int debounce[NUM_GPIO] = {0,0,0,0,0,0,0,0,0,0,0,0};
  int no_input = 0;
  int counter = 0;
  int errors = 0;
  char c = 0;
  char *input = NULL;

  while (run) {
    nanosleep(&delay, NULL);
    c = read_values(read, last, debounce);

    if (!c) {
      ++no_input;

      if (no_input >= _2s) {
	// no input for 2 seconds, reset input buffer
	printf("resetting input buffer\n");

	if (counter) {
	  counter = 0;
	  ++errors;

	  if (errors >= MAX_ERRORS) {
	    // trigger alarm
	    Keypad_setAlarm(1);
	    printf("ALARM 2s!!\n");
	  }
	}

	input = (char *) realloc(input, sizeof(char) * (counter + 1));
	input[counter] = '\0';
	no_input = 0;
      }
    } else {
      // add c to input buffer
      ++counter;
      no_input = 0;
      input = (char *) realloc(input, sizeof(char) * (counter + 1));
      input[counter - 1] = c;
      input[counter] = '\0';
      
      if (counter == code.size) {
	// check if the code matches
	if (strcmp(input, code.code) == 0) {
	  printf("CORRECT CODE!\n");
	  errors = 0;
	  Keypad_setAlarm(0);
	  codeEntered = 1;
	} else {
	  printf("INCORRECT CODE!\n");
	  ++errors;

	  if (errors >= MAX_ERRORS) {
	    // trigger the alarm
	    Keypad_setAlarm(1);
	    printf("ALARM!!\n");
	  }
	}

	counter = 0;
      }
    }
    
    for (int i = 0; i < NUM_GPIO; ++i) {
      last[i] = read[i];
    }
    }*/
  
  int read[NUM_GPIO] = {0,0,0,0,0,0,0,0,0,0,0,0};
  int last[NUM_GPIO] = {0,0,0,0,0,0,0,0,0,0,0,0};
  int debounce[NUM_GPIO] = {0,0,0,0,0,0,0,0,0,0,0,0};

  
  Keypad_setAlarm(1);

  while (1) {
    read_values(read,last,debounce);
    sleep(1);
  }

  return NULL;
}

static char read_values(int *read, int *last, int *debounce)
{
  FILE *file;
  char buffer[BUFFER_SIZE] = "";
  char result[32] = "";
  
  for (int i = 0; i < NUM_GPIO; ++i) {
    strcpy(buffer, GPIO_BASE_DIR "gpio");
    strcat(buffer, GPIO[i]);
    strcat(buffer, "/value");
    
    file = fopen(buffer, "r");
    if (file == NULL)
      printf("Couldn't read GPIO %s!", GPIO[i]);

    fgets(result, BUFFER_SIZE, file);
    fclose(file);

    if (result[0] == '1') {
      read[i] = 1;

      if (last[i] == 1)
	debounce[i] = 1;
      else
	debounce[i] = 0;

      if (debounce[i] == 1)
	continue;
      
      //printf("KEY %c PRESSED\n", KEYS[i]);

      // accepts only the first button pressed
      for (int j = i + 1; j < NUM_GPIO; ++j) {
	read[j] = 0;
	debounce[j] = 0;
      }
      
      return KEYS[i];
      
    } else {
      read[i] = 0;
      debounce[i] = 0;
    }
  }

  return 0;
}
