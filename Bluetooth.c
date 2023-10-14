#include <avr/interrupt.h>
#include "include/Bluetooth.h"
#include "include/Time_x.h"
#include "include/Buzz.h"
#include "include/TM1637_x.h"
#include "include/nap.h"

volatile unsigned char USART_data[8];

volatile unsigned char _data[4];


void __init__bluetooth()
{
	SREG |= (1<<7);

	//Enable Transmition and Reception
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);

	// Recieve complete enable
	UCSR0B |= (1<<RXCIE0);

	//Select mode-Asynchronous USART0
	UCSR0C &= (~(1<<UMSEL01)) & (~(1<<UMSEL00));

	//Parity desabled
	UCSR0C &= (~(1<<UPM01)) & (~(1<<UPM00));

	//Stop bit select-1
	UCSR0C &= ~(1<<USBS0);

	//selct the charactor size of the frame-8 bit
	UCSR0B &= ~(1<<UCSZ02);
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);

	//selct the boud rate 9600-103;
	UBRR0 = 103;

	//select the speed-2X
	UCSR0A &= ~(1<<U2X0);

	Transmitt("Hello");
}

ISR(USART_RX_vect)
{

	PORTB ^= (1<<PORTB5);

	for(uint8_t i=0; i<8; i++){

		while(!(UCSR0A & (1<<RXC0)));

		USART_data[i] = UDR0;

	}

	PORTB ^= (1<<PORTB5);

	_data[0] = USART_data[4];
	_data[1] = USART_data[5];
	_data[2] = USART_data[6];
	_data[3] = USART_data[7];


	if( (USART_data[0] == 'S') && (USART_data[1] == 'T') && (USART_data[2] == '-') && (USART_data[3] == '-') ){

		_setTime();

	
	}else if( (USART_data[0] == 'E') && (USART_data[1] == 'F') && (USART_data[2] == '-') && (USART_data[3] == '-') ){

		_selFormat();

	}else if( (USART_data[0] == 'S') && (USART_data[1] == 'A') && (USART_data[2] == '-') && (USART_data[3] == '-') ){

		_setAlarm();
		
	}else if( (USART_data[0] == 'P') && (USART_data[1] == 'A') && (USART_data[2] == '-') && (USART_data[3] == '-') ){

		_stopAlarm();
		
	}else if( (USART_data[0] == 'A') && (USART_data[1] == 'R') && (USART_data[2] == '-') && (USART_data[3] == '-') ){

		_setRing();
		
	}else if( (USART_data[0] == 'B') && (USART_data[1] == 'V') && (USART_data[2] == '-') && (USART_data[3] == '-') ){

		_setBuzzVol();
		
	}else if( (USART_data[0] == 'D') && (USART_data[1] == 'B') && (USART_data[2] == '-') && (USART_data[3] == '-') ){

		_setBri();
		
	}else if( (USART_data[0] == 'S') && (USART_data[1] == 'L') && (USART_data[2] == '-') && (USART_data[3] == '-') ){

		_sleepIt();
		
	}

	else{

		Transmitt("Error");
	}
	
}

void Transmitt(const unsigned char* dat)
{
	for (uint8_t i = 0; i < 6; i++){ 
	   
	   while (!(UCSR0A&(1<<UDRE0))){};

	   UDR0 = dat[i]; 
	
	}	
}


void _setTime()
{

	uint8_t hrs;
	uint8_t min;

	hrs = (((uint8_t)(_data[0] - '0')) * 10) + ((uint8_t)(_data[1] - '0'));

	min = ((uint8_t)(_data[2] - '0') * 10) + ((uint8_t)(_data[3] - '0'));

	setTime(hrs, min);

	Transmitt("Done.");

	butClick();
}

void _selFormat()
{
	if( (((((uint8_t)(_data[0] - '0')) * 10) + ((uint8_t)(_data[1] - '0'))) == 24) && (((uint8_t)(_data[2] - '0') * 10) + ((uint8_t)(_data[3] - '0')) == 0) ){

		editFormat(1);

		Transmitt("Done.");

		butClick();
	
	}
	else if( (((((uint8_t)(_data[0] - '0')) * 10) + ((uint8_t)(_data[1] - '0'))) == 12) && (((uint8_t)(_data[2] - '0') * 10) + ((uint8_t)(_data[3] - '0')) == 0) ){

		editFormat(2);

		Transmitt("Done.");

		butClick();
	
	}else{

		Transmitt("Error");
	}

}

void _setAlarm()
{
	uint8_t hrs;
	uint8_t min;

	hrs = (((uint8_t)(_data[0] - '0')) * 10) + ((uint8_t)(_data[1] - '0'));

	min = ((uint8_t)(_data[2] - '0') * 10) + ((uint8_t)(_data[3] - '0'));

	editAlarm(hrs, min);

	Transmitt("Done.");

	butClick();
}

void _stopAlarm()
{
	
	stopAlarm();
}

void _setRing()
{
	editRing( (uint8_t)(_data[3] - '0') );

	Transmitt("Done.");

	butClick();
}

void _setBuzzVol()
{
	setBuzzVol( (((uint8_t)(_data[2] - '0') * 10) + ((uint8_t)(_data[3] - '0'))) );

	Transmitt("Done.");

	butClick();
}

void _setBri()
{
	editBrightness( ((uint8_t)(_data[3] - '0')) );

	Transmitt("Done.");

	butClick();
}

void _sleepIt()
{
	sleepIt();

	Transmitt("Done.");

	butClick();
}

