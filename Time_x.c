#include <avr/interrupt.h>
#include <util/delay.h>
#include "include/Time_x.h"
#include "include/TM1637_x.h"
#include "include/Buzz.h"
#include "include/eeprom.h"

// Format select flag, default - 24 Hrs
volatile uint8_t _FORMAT_ = 1;

// Slect ring for the alarm
volatile uint8_t _RING_ = 1;

// Counter variables for time
volatile uint8_t _Hrs_ = 0;
volatile uint8_t _Min_ = 0;
volatile uint8_t _Sec_ = 0;

// Counter variabels for alarm
volatile uint8_t _AL_Hrs_ = 0;
volatile uint8_t _AL_Min_ = 0;

volatile uint8_t _Digit_ = 1;

// This flag is set by the sleepIt function in nap.h
volatile uint8_t NAP = 2;

void __init__timer()
{ 
 	// Enable the global Interrupt
	SREG |= (1<<7);
	// Enable the output compare match interrupt on comapare A 
	TIMSK1 |= (1<<OCIE1A);

	// Set TimerCounter1 in CTC mode
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);

	// Set the prescalr to 1024 so we get 15625 Hz pulses(counts) per second
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);

	// Assign the OCR1A to 46875 (3 seconds)
	OCR1A = 46875;

}

void ifNap(uint8_t nap)
{
	if(nap == 1)
	{
		NAP = 1;

	}else if(nap == 2){

		NAP = 2;
	}
}


ISR(TIMER1_COMPA_vect)
{	
	_Sec_ += 3;

	if( (_Sec_ == 60) || (_Sec_ > 60) )
	{

		_Sec_ = 0;
		_Min_ += 1;

		if( (_Min_ == 60) || (_Min_ > 60) )
		{

			_Min_ = 0;
			_Hrs_ += 1;

			if( (_Hrs_ == 25) || (_Hrs_ > 25) )
			{

				_Hrs_ = 1;

			}
		}

		if(NAP == 2){

			setTime(_Hrs_, _Min_);
			compAlarm();
		
		}else if(NAP == 1){

			eep_Write(HRS, _Hrs_);
			eep_Write(MIN, _Min_);

			compAlarm();
		
		}else{

			NAP = 2;
		}
		
	} 
}


void __timer__(uint8_t ST)
{
	// I think I need a better way to pause the TimerCounter1

	// Pause the TimerCounter1
	if(ST == 0){
		// Disable the output compare match on comapare A 
		TIMSK1 &= ~(1<<OCIE1A);
		TCCR1B &= ~(1<<CS10);
		TCCR1B &= ~(1<<CS11);
		TCCR1B &= ~(1<<CS12);
	}

	// Resume the TimerCounter1
	if(ST == 1){
		_Sec_ = 0;
		// Start counting agin from 0
		TCCR1B |= (1<<CS10);
		TCCR1B &= ~(1<<CS11);
		TCCR1B |= (1<<CS12);
		TCNT1 = 0;
		// Enable the output compare match on comapare A 
		TIMSK1 |= (1<<OCIE1A);
	}
}

// To init the data from eeprom
void initTime()
{
	_Hrs_ = eep_Read(HRS);
	_Min_ = eep_Read(MIN);

	if( (_Hrs_ > 24) || (_Min_ > 60) ){ _Hrs_ = 0; _Min_ = 0; }
}

void initFormat()
{
	_FORMAT_ = eep_Read(FORMAT);

	if( (_FORMAT_ == 0) || (_FORMAT_ > 2) ){ _FORMAT_ = 1; }
}

void initAlarm()
{
	_AL_Hrs_ = eep_Read(AHRS);
	_AL_Min_ = eep_Read(AMIN);

	if( (_AL_Hrs_ > 24) || (_AL_Min_ > 60) ){ _AL_Hrs_ = 0; _AL_Min_ = 0; }
}

void initRing()
{
	_RING_ = eep_Read(ARING);
	if( (_RING_ == 0) || (_RING_ > 3) ){ _RING_ = 1; }
}

void showTime()
{
	TMx_printText("--:--");
	_delay_ms(500);

	initTime();
	initFormat();
	setTime(_Hrs_, _Min_);

	initAlarm();
	initRing();
	initVol();
	// Make sure to call this function at last - like this
	// Because this function can enable ADC_vect interrupt
	initBri();
}

void setTime(uint8_t hrs, uint8_t min)
{
	_Hrs_ = hrs;
	_Min_ = min;

	if(_FORMAT_ == 1){ TMx_printTime(_Hrs_, _Min_); }

	if(_FORMAT_ == 2){

		if(_Hrs_ >= 13){

			TMx_printTime((_Hrs_ - 12), _Min_);

		}else{

			TMx_printTime(_Hrs_, _Min_); 
		}
	}
	_Sec_ = 0;
	TCNT1 = 0;

	eep_Write(HRS, _Hrs_);
	eep_Write(MIN, _Min_);
}

void editTime()
{
	_Digit_ = 1;

	TMx_printText("-Et-");
	_delay_ms(500);

	TMx_printTime(_Hrs_, _Min_);
}

void incTime()
{
	if(_Digit_ == 2){

		_Min_ += 1;

		if( (_Min_ == 60) || (_Min_ > 60) ){ _Min_ = 0;	}

		TMx_printTime(_Hrs_, _Min_);
	}
	if(_Digit_ == 1){

		_Hrs_ += 1;

		if( (_Hrs_ == 25) || (_Hrs_ > 25) ){ _Hrs_ = 1; }

		TMx_printTime(_Hrs_, _Min_);
	}
	eep_Write(HRS, _Hrs_);
	eep_Write(MIN, _Min_);
}

void decTime()
{
	if(_Digit_ == 2){

		if(_Min_ != 0){ _Min_ -= 1; }

		if(_Min_ == 0){ _Min_ = 59; }

		TMx_printTime(_Hrs_, _Min_);
	}
	if(_Digit_ == 1){

		if(_Min_ != 0){ _Hrs_ -= 1; }

		if(_Hrs_ == 0){ _Hrs_ = 24; }

		TMx_printTime(_Hrs_, _Min_);
	}
	eep_Write(HRS, _Hrs_);
	eep_Write(MIN, _Min_);
}

void selDigit(uint8_t sel)
{
	_Digit_ = sel;
}

void editFormat(uint8_t _F)
{
	_FORMAT_ = _F;
	
	eep_Write(FORMAT, _FORMAT_);

	setTime(_Hrs_, _Min_);
}

void selFormat(uint8_t _F)
{
	_Digit_ = 1;

	TMx_printText("-EF-");
	_delay_ms(500);

	if(_FORMAT_ == 1){ TMx_printTime(24, 00); }

	if(_FORMAT_ == 2){ TMx_printTime(12, 00); }
}

void nextFormat()
{
	_FORMAT_ += 1;

	if( (_FORMAT_ == 3) || (_FORMAT_ > 3) ){ _FORMAT_ = 1; }

	if(_FORMAT_ == 1){ TMx_printTime(24, 00); eep_Write(FORMAT, _FORMAT_); }

	if(_FORMAT_ == 2){ TMx_printTime(12, 00); eep_Write(FORMAT, _FORMAT_); }
}

void prevFormat()
{
	if(_FORMAT_ != 0){ _FORMAT_ -= 1; }

	if(_FORMAT_ == 0){ _FORMAT_ = 2; }

	if(_FORMAT_ == 1){ TMx_printTime(24, 00); eep_Write(FORMAT, _FORMAT_); }

	if(_FORMAT_ == 2){ TMx_printTime(12, 00); eep_Write(FORMAT, _FORMAT_); }
}

void editAlarm(uint8_t hrs, uint8_t min)
{
	_AL_Hrs_ = hrs;
	_AL_Min_ = min;

	eep_Write(AHRS, _AL_Hrs_);
	eep_Write(AMIN, _AL_Min_);
}

void setAlarm()
{
	_Digit_ = 1;

	TMx_printText("-AL-");
	_delay_ms(500);

	TMx_printTime(_AL_Hrs_, _AL_Min_);
}

void incAlarm()
{
	if(_Digit_ == 2){

		_AL_Min_ += 1;

		if( (_AL_Min_ == 60) || (_AL_Min_ > 60) ){ _AL_Min_ = 0; }

		TMx_printTime(_AL_Hrs_, _AL_Min_);
	}
	if(_Digit_ == 1){

		_AL_Hrs_ += 1;

		if( (_AL_Hrs_ == 25) || (_AL_Hrs_ > 25) ){ _AL_Hrs_ = 0; }

		TMx_printTime(_AL_Hrs_, _AL_Min_);
	}
	eep_Write(AHRS, _AL_Hrs_);
	eep_Write(AMIN, _AL_Min_);
}

void decAlarm()
{
	if(_Digit_ == 2){

		if(_AL_Min_ != 0){ _AL_Min_ -= 1; }

		if(_AL_Min_ == 0){ _AL_Min_ = 59; }

		TMx_printTime(_AL_Hrs_, _AL_Min_);
	}

	if(_Digit_ == 1){

		if(_AL_Hrs_ != 0){

			_AL_Hrs_ -= 1;
		}
		if(_AL_Hrs_ == 0){

			_AL_Hrs_ = 24;
		}

		TMx_printTime(_AL_Hrs_, _AL_Min_);
	}
	eep_Write(AHRS, _AL_Hrs_);
	eep_Write(AMIN, _AL_Min_);
}

void compAlarm()
{
	if( (_Hrs_ == _AL_Hrs_) && (_Min_ == _AL_Min_) ){

		PORTB |= (1<<PORTB5);
		ringAlarm(_RING_);
		PORTB &= ~(1<<PORTB5);
	}
}

void editRing(uint8_t r)
{
	_RING_ = r;
	eep_Write(ARING, _RING_);
}

void setRing()
{
	TMx_printText("-At-");
	_delay_ms(500);

	TMx_printNum(_RING_);
	ringAlarm(_RING_);
}

void nextRing()
{
	_RING_ += 1;

	if( (_RING_ == 4) || (_RING_ > 4) ){ _RING_ = 1; }

	TMx_printNum(_RING_);
	ringAlarm(_RING_);
	eep_Write(ARING, _RING_);
}

void prevRing()
{
	if(_RING_ != 0){ _RING_ -= 1; }

	if(_RING_ == 0){ _RING_ = 3; }

	TMx_printNum(_RING_);
	ringAlarm(_RING_);
	eep_Write(ARING, _RING_);
}


