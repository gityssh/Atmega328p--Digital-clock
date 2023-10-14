#include <avr/sleep.h>

#include "include/nap.h"
#include "include/AutoB.h"
#include "include/TM1637_x.h"
#include "include/Time_x.h"
#include "include/Buzz.h"

volatile uint8_t FLAG_NAP = 0;

void sleepIt()
{
	FLAG_NAP += 1;

	if(FLAG_NAP == 1)
	{
		ifNap(FLAG_NAP);

		turnOffAutoB();
		TMx_turnOff();
		stopBuzz();
	}
	else if(FLAG_NAP == 2)
	{
		ifNap(FLAG_NAP);

		showTime();
		FLAG_NAP = 0;
	}
}

