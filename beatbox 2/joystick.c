#include "joystick.h"

#define UP 		26
#define DOWN 	46
#define LEFT 	65
#define RIGHT 	47
#define IN 		27

#define JOYSTICK_UP_PIN_PATH "/sys/class/gpio/gpio26/value"
#define JOYSTICK_DOWN_PIN_PATH "/sys/class/gpio/gpio46/value"
#define JOYSTICK_LEFT_PIN_PATH "/sys/class/gpio/gpio65/value"
#define JOYSTICK_RIGHT_PIN_PATH "/sys/class/gpio/gpio47/value"
#define JOYSTICK_IN_PIN_PATH "/sys/class/gpio/gpio27/value"

#define EXPORT_FILE    "/sys/class/gpio/export"
#define BUFF_SIZE 1024

void joystick_setup(int pin)
{
	char buff[BUFF_SIZE];

	// set up for joystick inputs
	FILE* pExportFile = fopen(EXPORT_FILE,"w");
	if( !pExportFile)
	{
		printf("Error opening file %s\n", EXPORT_FILE);
		exit(1);
	}
	fprintf(pExportFile, "%d", pin);
	fclose(pExportFile);

	// set direction
	sprintf(buff,"/sys/class/gpio/gpio%d/direction", pin);
	FILE* pDirectionFile = fopen(buff, "w");
	if (!pDirectionFile) {
		printf("Error opening file %s\n", buff);
		exit(1);
	}
	fprintf(pDirectionFile, "in");
	fclose(pDirectionFile);
}

void joystick_init()
{
	joystick_setup(UP);
	joystick_setup(DOWN);
	joystick_setup(LEFT);
	joystick_setup(RIGHT);
	joystick_setup(IN);
}

int read_file_to_screen(char* filename)
{
	FILE *file = fopen(filename, "r");
	if(file == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n",filename);
		exit(-1);
	}

	const int max_length = 1024;
	char buff[max_length];
	fgets(buff,max_length,file);

	// close
	fclose(file);
	int return_joystick_value = atoi(buff);
	return return_joystick_value;
}

int readLineFromFile(char* file_name, char* buff, unsigned int max_length)
{
	FILE *file = fopen(file_name, "r");
	if (file == NULL) {
		printf("FILEIODRV ERROR: Unable to open file for read: %s\n", file_name);
		exit(-1);
	}

	// Read string (line)
	int bytes_read = getline(&buff, &max_length, file);

	// Close
	fclose(file);

	// Null terminate "string" being returned
	buff[bytes_read] = 0;

	return bytes_read;
}


_Bool isJoystickPressed(int pin)
{
	char fileName[BUFF_SIZE];
	sprintf(fileName, "/sys/class/gpio/gpio%d/value", pin);
	char buff[BUFF_SIZE];
	readLineFromFile(fileName, buff, BUFF_SIZE);
	return buff[0] == '0';
}

void* joystickThread(void* arg)
{

	joystick_init();
	while(!stopping)
	{
		nanoSleepFunc(1, 0);
		if(isJoystickPressed(UP))
			AudioMixer_setVolume(AudioMixer_getVolume()+5);
		if(isJoystickPressed(DOWN))
			AudioMixer_setVolume(AudioMixer_getVolume()-5);
		if(isJoystickPressed(LEFT))
			AudioMixer_setBPM(AudioMixer_getBPM() - 5);
		if(isJoystickPressed(RIGHT))
			AudioMixer_setBPM(AudioMixer_getBPM() + 5);
		if(isJoystickPressed(IN))
		{
			rock_status++;
			if(rock_status == 3)
				rock_status = 0;
		}
	}
	pthread_exit(0);
}