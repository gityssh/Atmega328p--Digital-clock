#ifndef __Time_x__
	#define __Time_x__

// Avr I/O lib
#include <avr/io.h>

void showTime();

// Set Hrs, Min and second variable
void setTime(uint8_t hrs, uint8_t min);

// Edit Time
void editTime();
void incTime();
void decTime();
void selDigit(uint8_t sel);

// To init the data from eeprom
void initTime();
void initFormat();
void initAlarm();
void initRing();

// Select Format
void editFormat(uint8_t _F);
void selFormat(uint8_t _F);
void nextFormat();
void prevFormat();

// Set Alarm 
void editAlarm(uint8_t hrs, uint8_t min);
void setAlarm();
void incAlarm();
void decAlarm();
void compAlarm();


// Set Ringtone 
void editRing(uint8_t r);
void setRing();
void nextRing();
void prevRing();

// If nap enabled
void ifNap(uint8_t nap);

// Initialize the timercounter1
void __init__timer();

// Turn on or off the TimerCounter1
void __timer__(uint8_t ST);

#endif