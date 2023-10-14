#include <avr/io.h>
#include <avr/interrupt.h>

#include "include/TM1637_x.h"
#include "include/Time_x.h"
#include "include/ButtonINT.h"
#include "include/Buzz.h"
#include "include/AutoB.h"
#include "include/Bluetooth.h"
#include "include/eeprom.h"


int main()
{
	// PB5
	DDRB |= (1<<DDB5);

	__init__AutoB();

	showTime();

	__init__timer();

	__init__button();

	__init__Buzz();

	__init__eeprom();

	__init__bluetooth();


	while(1)
	{	
		
	}

	return 0;
}


