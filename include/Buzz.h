#ifndef __Buzz__
	#define __Buzz__

// Avr I/O lib
#include <avr/io.h>

// Initialize the buzzer
void __init__Buzz();

// Set the volume
void setBuzzVol(uint8_t v);

// To init the data from eeprom
void initVol();

// Set Buzzer volume
void setVol();
void incVol();
void decVol();

// Button Click sound
void butClick();

// Alarm ring sound
void ringAlarm(uint8_t R);

// Stop Buzz
void stopBuzz();

// Stop Alarm
void stopAlarm();

// Turn On buzz
void turnOnBuzz();


#endif