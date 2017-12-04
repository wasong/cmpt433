// Controls door sensor (adafru.it/375)
// out: 3.3v VDD
// in: GPIO68

#ifndef _DOOR_SENSOR
#define _DOOR_SENSOR

// Initialize/uninitialize pins for use by the door sensor
void Door_init();
void Door_unInit();

#endif
