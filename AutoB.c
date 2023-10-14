#include "include/AutoB.h"
#include "include/TM1637_x.h"
#include <avr/interrupt.h>

volatile uint8_t lvl_AI[] = {1, 2, 3, 4, 5, 6, 7};

void __init__AutoB()
{
	// Make ADC pin 3 as input 
	DDRC &= ~(1<<DDC3);

	SREG |= (1<<7);

	//set prescalar for ADC to oprate on -128
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);

	//select the referance voltage
	ADMUX |= (1<<REFS0);
	ADMUX &= (~(1<<REFS1));

	//select the input channel - PC3
	ADMUX |= (1<<MUX0);
	ADMUX |= (1<<MUX1);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX3);
}

void turnOnAutoB()
{
	//configure ADCSRA
	ADCSRA |= (1<<ADEN) | (1<<ADIE);

	//ADC start conversion bit
	ADCSRA |= (1<<ADSC);
}

void turnOffAutoB()
{
	//configure ADCSRA
	ADCSRA &= (~(1<<ADEN)) & (~(1<<ADIE));
}


ISR(ADC_vect, ISR_NOBLOCK)
{

	//Serial.println(ADC);
	if( (ADC > 0) && (ADC < 150) ){

		TMx_setBrightness(lvl_AI[0]);
	}
	else if( (ADC > 250) && (ADC < 400) ){

		TMx_setBrightness(lvl_AI[1]);
	}
	else if( (ADC > 500) && (ADC < 600) ){

		TMx_setBrightness(lvl_AI[1]);
	}
	else if( (ADC > 650) && (ADC < 700) ){

		TMx_setBrightness(lvl_AI[2]);
	}
	else if( (ADC > 750) && (ADC < 800) ){

		TMx_setBrightness(lvl_AI[2]);
	}
	else if( (ADC > 850) && (ADC < 900) ){

		TMx_setBrightness(lvl_AI[3]);
	}
	else if( (ADC > 950) && (ADC < 1023) ){

		TMx_setBrightness(lvl_AI[5]);
	}

	//ADC start conversion bit
	ADCSRA |= (1<<ADSC);
}

