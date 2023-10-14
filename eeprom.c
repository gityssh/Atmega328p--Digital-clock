#include "include/eeprom.h"

void __init__eeprom()
{
	// Nothing needs to initailize for now
}

void eep_Write(uint8_t _add, uint8_t _dat)
{
	// wait for the unfinished process if any
	while(EECR&(1<<EEPE)); 	

	EEAR = _add;
	
	EEDR = _dat;
	
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
}

uint8_t eep_Read(uint8_t _add)
{
	// wait for the unfinished process if any
	while(EECR&(1<<EEPE)); 
	
	EEAR = _add;

	EECR |= (1<<EERE);
	EECR |= (1<<EEPE);

	return EEDR;
}

