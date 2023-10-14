#include <util/delay.h>
#include "include/Buzz.h"
#include "include/TM1637_x.h"
#include "include/eeprom.h"

volatile uint8_t _FLAG_ALARM_ON = 0;
volatile uint8_t vol = 3;

void __init__Buzz()
{
	//configure the TimerCounter2 as fast pwm mode
	TCCR2A |= (1<<WGM20);
	TCCR2A |= (1<<WGM21);
	TCCR2B &= (~(1<<WGM22));

	DDRD |= (1<<DDD3);
}

void initVol()
{
	vol = eep_Read(BVOL);
	if(vol > 20){ vol = 3; }
}

void setBuzzVol(uint8_t v)
{
	if(vol >= 21){

		vol = 1;
	}

	vol = v;

	eep_Write(BVOL, vol);

	butClick();
}


void setVol()
{
	TMx_printText("-bU-");
	_delay_ms(500);

	TMx_printNum(vol);
	setBuzzVol(vol);
}

void incVol()
{
	vol += 1;

	if(vol >= 21){

		vol = 1;
	}
	TMx_printNum(vol);
	setBuzzVol(vol);
}

void decVol()
{
	if(vol != 0)
	{
		vol -= 1;
	}

	if(vol == 0){

		vol = 20;
	}

	TMx_printNum(vol);
	setBuzzVol(vol);
}


void butClick()
{
	turnOnBuzz();

	OCR2B = vol;
	_delay_ms(100);
	OCR2B = 0;
	_delay_ms(100);

	stopBuzz();
}

void ringAlarm(uint8_t R)
{
	turnOnBuzz();

	_FLAG_ALARM_ON = 1;

	if(R == 1){

		// Here should be a pattern for the alarm ring
		OCR2B = vol;
	}
}

void stopBuzz()
{
	TCCR2A &= (~(1<<COM2B0)) & (~(1<<COM2B1));
	TCCR2B &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
}

void stopAlarm()
{
	if(_FLAG_ALARM_ON == 1){

		_FLAG_ALARM_ON = 0;

		TCCR2A &= (~(1<<COM2B0)) & (~(1<<COM2B1));
		TCCR2B &= (~(1<<CS20)) & (~(1<<CS21)) & (~(1<<CS22));
	}
}

void turnOnBuzz()
{
	//set the prescalar-32
	TCCR2B |= (1<<CS20);
	TCCR2B |= (1<<CS21);
	TCCR2B &= ~(1<<CS22);

	//set the compare output match registor - Non-inverted mode
	TCCR2A |= (1<<COM2B1);
	TCCR2A &= ~(1<<COM2B0);
}