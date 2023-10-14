#ifndef __Bluetooth__
	#define __Bluetooth__

/*

	1) ST--0000  --> Set Time
	2) EF--0000  --> Set Format
	3) SA--0000	 --> Set Alarm
	4) PA--0000  --> Pause Alarm
	5) AR--0000  --> Set Alarm Ringtone
	6) BV--0000  --> Set Buzzer Volume
	7) DB--0000  --> Set Display Brightness
	8) SL--0000  --> Sleep

*/

#include <avr/io.h>

// Initialize the the button/buttons
void __init__bluetooth();

void Transmitt(const unsigned char* dat);

void _setTime();

void _selFormat();

void _setAlarm();

void _stopAlarm();

void _setRing();

void _setBuzzVol();

void _setBri();

void _sleepIt();

#endif