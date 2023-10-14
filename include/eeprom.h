#ifndef __eeprom__
	#define __eeprom__

#include <avr/io.h>

// EEPROM addresses for perticular data 
#define HRS 0x10
#define MIN 0x11
#define FORMAT 0x12
#define AHRS 0x13
#define AMIN 0x14
#define ARING 0x15
#define BVOL 0x16
#define DBRI 0x17

// Initialize the the eeprom
void __init__eeprom();

// Make sure to only call this function in an/any ISR(Not the Nested one)
// write data to eeprom 
void eep_Write(uint8_t _add, uint8_t _dat);

// Make sure to only call this function in an/any ISR(Not the Nested one)
// read from the eeprom 
uint8_t eep_Read(uint8_t _add);


#endif