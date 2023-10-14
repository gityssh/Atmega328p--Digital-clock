#include <avr/interrupt.h>
#include <util/delay.h>
#include "include/TM1637_x.h"
#include "include/ButtonINT.h"
#include "include/Time_x.h"
#include "include/Buzz.h"
#include "include/nap.h"

volatile uint8_t _FLAG_SEL = 0;
volatile uint8_t _FLAG_DIGIT = 1;

void __init__button()
{
		// Enable Global interrupt
		SREG |= (1<<7);

		// make thease pins as Input and enable internal pull-up
		DDRD &= ~(1<<DDD7);
		PORTD |= (1<<PORTD7);
		DDRD &= ~(1<<DDD6);
		PORTD |= (1<<PORTD6);
		DDRD &= ~(1<<DDD5);
		PORTD |= (1<<PORTD5);
    
		// Port D as PCINT
		PCICR |= (1<<PCIE2);
		PCMSK2 |= (1<<PCINT21);
		PCMSK2 |= (1<<PCINT22);
		PCMSK2 |= (1<<PCINT23);
}


ISR(PCINT2_vect)
{

		if( (!(PIND & (1<<7))) && ((PIND & (1<<6))) && ((PIND & (1<<5))) )
		{

				butClick();

				// Pause the Timer
		 		__timer__(0);

				_FLAG_SEL += 1;

				// Edit Time 
				if(_FLAG_SEL == 1){

						_FLAG_DIGIT = 1;
						// Edit Time
			   		editTime();

			  }

			  // Set format
		   	if(_FLAG_SEL == 2){
		   		
		   		  _FLAG_DIGIT = 1;
		   		  // Select the Time format
		   		  selFormat(0);
		   	}

		   	// Set Alarm 
		   	if(_FLAG_SEL == 3){
		   	    	
			   		// Set Alarm 
			   		setAlarm();

		   	}

		   	// Set Alarm Ring 
		   	if(_FLAG_SEL == 4){
		   	    	
			   		// Set Alarm Ring 
			   		setRing();

		   	}

		   	// Set Buzzer Volume 
		   	if(_FLAG_SEL == 5){
		   	    	
			   		// Set Buzzer Volume 
			   		setVol();

		   	}

		   	// Set Display Brightness 
		   	if(_FLAG_SEL == 6){
		   	    	
			   		setBrightness();
		   	}


		   	// Resume Timer
		   	if(_FLAG_SEL == 7){

		   			_FLAG_SEL = 0;
		   			// Resumes the Timer
			   		__timer__(1);
			   		showTime();			  
			  }
			  _delay_ms(200);
		}


		// Set Time Increase , Decrease and Digit
		if( (((PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 1) )
		{
			  butClick();

				incTime();
				_delay_ms(200);
		}
		if( ((!(PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 1) )
		{
				butClick();

				decTime();
				_delay_ms(200);
		}
		if( (((PIND & (1<<7))) && ((PIND & (1<<6))) && (!(PIND & (1<<5)))) && (_FLAG_SEL == 1) )
		{
				butClick();

				_FLAG_DIGIT += 1;
			  if(_FLAG_DIGIT == 1){
			  		selDigit(1);
			  }
			  if(_FLAG_DIGIT == 2){
			  	  selDigit(2);
			  }
			  if(_FLAG_DIGIT == 3){
			  	  _FLAG_DIGIT = 1;
			  	  selDigit(1);
			  }
			  _delay_ms(200);
		}



		// Select the time format next , previous
		if( (((PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 2) )
		{
				butClick();

				nextFormat();
				_delay_ms(200);
		}
		if( ((!(PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 2) )
		{
				butClick();

				prevFormat();
				_delay_ms(200);
		}
		if( (((PIND & (1<<7))) && ((PIND & (1<<6))) && (!(PIND & (1<<5)))) && (_FLAG_SEL == 2) )
		{
				// NOP
		}




		// Set Alarm Increase , Decrease and sel digit
		if( (((PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 3) )
		{
				butClick();

				incAlarm();
				_delay_ms(200);
		}
		if( ((!(PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 3) )
		{
				butClick();

				decAlarm();
				_delay_ms(200);
		}
		if( (((PIND & (1<<7))) && ((PIND & (1<<6))) && (!(PIND & (1<<5)))) && (_FLAG_SEL == 3) )
		{
				butClick();

				_FLAG_DIGIT += 1;
			  if(_FLAG_DIGIT == 1){
			  		selDigit(1);
			  }
			  if(_FLAG_DIGIT == 2){
			  	  selDigit(2);
			  }
			  if(_FLAG_DIGIT == 3){
			  	  _FLAG_DIGIT = 1;
			  	  selDigit(1);
			  }
			  _delay_ms(200);
		}



		// Select the time ring next , previous
		if( (((PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 4) )
		{
				butClick();

				nextRing();
				_delay_ms(200);
		}
		if( ((!(PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 4) )
		{
				butClick();
				
				prevRing();
				_delay_ms(200);
		}
		if( (((PIND & (1<<7))) && ((PIND & (1<<6))) && (!(PIND & (1<<5)))) && (_FLAG_SEL == 4) )
		{
				// NOP
		}




		// Select the volume ring next , previous
		if( (((PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 5) )
		{
				butClick();

				incVol();

				_delay_ms(200);
		}
		if( ((!(PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 5) )
		{
				butClick();
				
				decVol();

				_delay_ms(200);
		}
		if( (((PIND & (1<<7))) && ((PIND & (1<<6))) && (!(PIND & (1<<5)))) && (_FLAG_SEL == 5) )
		{
				// NOP
		}



		// Select the Brightness inc , dec
		if( (((PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 6) )
		{
				butClick();

				incBri();

				_delay_ms(200);
		}
		if( ((!(PIND & (1<<7))) && (!(PIND & (1<<6))) && ((PIND & (1<<5)))) && (_FLAG_SEL == 6) )
		{
				butClick();
				
				decBri();

				_delay_ms(200);
		}
		if( (((PIND & (1<<7))) && ((PIND & (1<<6))) && (!(PIND & (1<<5)))) && (_FLAG_SEL == 6) )
		{
				// NOP
		}




		// This will stop the alarm
		if( ((!(PIND & (1<<7))) && ((PIND & (1<<6))) && (!(PIND & (1<<5)))) )
		{
				butClick();

				_FLAG_SEL = 0;
	   			// Resumes the Timer
		   		__timer__(1);
		   		showTime();	
				
				_delay_ms(200);
		}

		// This will Enable sleep mode
		if( (((PIND & (1<<7))) && (!(PIND & (1<<6))) && (!(PIND & (1<<5)))) && (_FLAG_SEL == 0) )
		{
				butClick();

				sleepIt();

				_delay_ms(200);
		}

		// This will - IDK
		if( ((!(PIND & (1<<7))) && (!(PIND & (1<<6))) && (!(PIND & (1<<5)))) && (_FLAG_SEL == 0) )
		{
				butClick();
				
				stopAlarm();

				_delay_ms(200);
		}

}

