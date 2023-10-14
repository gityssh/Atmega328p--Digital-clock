#ifndef __TM1637_x__
	#define __TM1637_x__

// Avr I/O lib
#include <avr/io.h>

// Duplicate i2c protocol speed
#define _bitdelay_ 1

// Initialize the TM1637 module's IO pins
void __init__TM();

// Turn it off
void TMx_turnOff();

// Start command
void CMD_start();

// Stop command
void CMD_stop();

// Write command and the data/address
void CMD_write(uint8_t byt);

// This function will print the time in decimal on the TM1637 display ex. |12:14|
// Max value is |99:99|
void TMx_printTime(uint8_t hr,uint8_t min);

// Print text on the Display
void TMx_printText(const unsigned char* txt);

// Print number on the Display
void TMx_printNum(uint16_t nm);

// Set brightness min-> 0 to max-> 7
void TMx_setBrightness(uint8_t lvl);

void editBrightness(uint8_t b);

// To init the data from eeprom
void initBri();

// set Brightness absract
void setBrightness();
void incBri();
void decBri();

#endif

