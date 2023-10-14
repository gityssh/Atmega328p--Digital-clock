#include "include/TM1637_x.h"
#include "include/AutoB.h"
#include <util/delay.h>
#include "include/eeprom.h"

// Default Brightness level: 0
volatile uint8_t BRIGHTNESS = 0x88;
volatile uint8_t Bri = 1;

// #define SEG_A   0b00000001
// #define SEG_B   0b00000010
// #define SEG_C   0b00000100
// #define SEG_D   0b00001000
// #define SEG_E   0b00010000
// #define SEG_F   0b00100000
// #define SEG_G   0b01000000
// #define SEG_DP  0b10000000

void __init__TM()
{
	// Make both lines GND to be pulled-up
	DDRB &= ~(1<<DDB4); //CLK
	DDRB &= ~(1<<DDB3); //DIO
	// Make both pins LOW-GND
	PORTB &= ~(1<<PORTB4);
	PORTB &= ~(1<<PORTB3);
}

void TMx_turnOff()
{
	__init__TM();

	CMD_start();
	CMD_write(0x44);
	CMD_stop();

	CMD_start();
	CMD_write(0xC0);
	CMD_write(0x00);
	CMD_stop();
	CMD_start();
	CMD_write(0xC1);
	CMD_write(0x00);
	CMD_stop();

	CMD_start();
	CMD_write(0xC2); // command-2
	CMD_write(0x00);
	CMD_stop();
	CMD_start();
	CMD_write(0xC3); // command-2
	CMD_write(0x00);
	CMD_stop();

	// Command- Turn on the LED and set brightness + brightness
	CMD_start();
	CMD_write(0x00);
	CMD_stop();
}


void CMD_start()
{
	// Make DIO pin as GND-LOW - because before it was HIGH
	DDRB |= (1<<DDB3); //DIO
	_delay_ms(_bitdelay_);
}

void CMD_stop()
{
	// Keep DIO pin to VCC
	DDRB |= (1<<DDB3); //DIO
	_delay_ms(_bitdelay_);
	// Make CLK to GND
	DDRB &= ~(1<<DDB4); //CLK
	_delay_ms(_bitdelay_);
	// Now make DIO line to GND
	DDRB &= ~(1<<DDB3); //DIO
	_delay_ms(_bitdelay_);
}

void CMD_write(uint8_t byt)
{
	uint8_t data = byt;

	// 8 data bits
	for(uint8_t i=0; i<8; i++)
	{
		// Make CLK LOW
		DDRB |= (1<<DDB4); //CLK
		_delay_ms(_bitdelay_);

		// Set data bits
		if(data & 0x01){
			DDRB &= ~(1<<DDB3); //DIO
		}else{
			DDRB |= (1<<DDB3); //DIO
		}
		_delay_ms(_bitdelay_);

		// Now make CLk HIGH
		DDRB &= ~(1<<DDB4); //CLK
		_delay_ms(_bitdelay_);

		// Right shift data byte so we can send all 8 bits from the DIO line
		data = data >> 1; 
	}

	// Wait for ACK
	// CLk to zero
	DDRB |= (1<<DDB4); //CLK
	// DIO as Input-GND
	DDRB &= ~(1<<DDB3); //DIO
	_delay_ms(_bitdelay_);

	// CLK to HIGH
	DDRB &= ~(1<<DDB4); //CLK
	_delay_ms(_bitdelay_);
	uint8_t ack = (DDRB & (1<<DDB3));
	if(ack == 0){
		DDRB |= (1<<DDB3); //DIO
	}
	_delay_ms(_bitdelay_);
	DDRB |= (1<<DDB4); //CLK
	_delay_ms(_bitdelay_); // we made both lines as actual LOW-VCC because the stop condition has yet to come	
}

void TMx_printTime(uint8_t hr, uint8_t min)
{
	// This logic below separates the a decimal value into two parts
	uint8_t fHrDigit = hr/10;
	uint8_t sHrDigit = hr-(fHrDigit*10);
	uint8_t fMinDigit = min/10;
	uint8_t sMinDigit = min-(fMinDigit*10);

	// Possible decimal values
	const uint8_t deciVal[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

	// Initialize the CLK and DIO pins
	__init__TM();

	CMD_start();
	CMD_write(0x44);
	CMD_stop();

	CMD_start();
	CMD_write(0xC0);
	CMD_write(deciVal[fHrDigit]);
	CMD_stop();
	CMD_start();
	CMD_write(0xC1);
	CMD_write(deciVal[sHrDigit] + 0x80);
	CMD_stop();

	CMD_start();
	CMD_write(0xC2); // command-2
	CMD_write(deciVal[fMinDigit]);
	CMD_stop();
	CMD_start();
	CMD_write(0xC3); // command-2
	CMD_write(deciVal[sMinDigit]);
	CMD_stop();

	// Command- Turn on the LED and set brightness + brightness
	CMD_start();
	CMD_write(BRIGHTNESS);
	CMD_stop();
}

void TMx_printText(const unsigned char* txt)
{
	// Respective Idenx:        0      1     2     3     4     5     6     7     8     9     10    11    12    13    14    15   16    17    18    19    20    21    22    23    24    25    26    27    28    29    30    31    32    33     34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49   50
	const uint8_t textVal[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x77, 0x7C, 0x7C, 0x39, 0x58, 0x5E, 0x5E, 0x79, 0x79, 0x71, 0x71, 0x2F, 0x2F, 0x76, 0x74, 0x10, 0x10, 0x1E, 0x1E, 0x70, 0x70, 0x38, 0x38, 0x54, 0x54, 0x5C, 0x5C, 0x73, 0x73, 0x67, 0x67, 0x50, 0x50, 0x78, 0x78, 0x3E, 0x1C, 0x80, 0x40, 0x08};
	// Respective values:       0      1     2	   3     4     5     6     7     8     9     A     a     B     b     C     c     D     d     E    e     F     f     G     g 	 H     h     I     i     J     j     K     k      L     l    N     n     O     o    P      p     Q     q     R     r     T     t     U     u    :     -     _
	// Possible charactors
	const unsigned char textChar[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H',
									  'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'N', 'n', 'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'T', 't', 'U', 'u', ':', '-', '_'};

	uint8_t cNDIndex[5] = {0x40, 0x40, 0x40, 0x40, 0x40};

	for(uint8_t j=0; j<=4; j++)
	{
		for(uint8_t i=0; i<=50; i++)
		{
			if(txt[j] == textChar[i])
			{
				cNDIndex[j] = textVal[i];
			}
		}
	}
	
	if(txt[4] == '\0'){

		// That means charactors in the text are 4
		// Initialize the CLK and DIO pins
		__init__TM();

		CMD_start();
		CMD_write(0x44);
		CMD_stop();

		CMD_start();
		CMD_write(0xC0);
		CMD_write(cNDIndex[0]);
		CMD_stop();

		CMD_start();
		CMD_write(0xC1);
		CMD_write(cNDIndex[1]);
		CMD_stop();

		CMD_start();
		CMD_write(0xC2); // command-2
		CMD_write(cNDIndex[2]);
		CMD_stop();

		CMD_start();
		CMD_write(0xC3); // command-2
		CMD_write(cNDIndex[3]);
		CMD_stop();

		// Command- Turn on the LED and set brightness + brightness
		CMD_start();
		CMD_write(BRIGHTNESS);
		CMD_stop();
	
	}else{

		// That means charactors in the text are 5
		// Initialize the CLK and DIO pins
		__init__TM();

		CMD_start();
		CMD_write(0x44);
		CMD_stop();

		CMD_start();
		CMD_write(0xC0);
		CMD_write(cNDIndex[0]);
		CMD_stop();

		CMD_start();
		CMD_write(0xC1);
		CMD_write(cNDIndex[1] + 0x80);
		CMD_stop();

		CMD_start();
		CMD_write(0xC2); // command-2
		CMD_write(cNDIndex[3]);
		CMD_stop();

		CMD_start();
		CMD_write(0xC3); // command-2
		CMD_write(cNDIndex[4]);
		CMD_stop();

		// Command- Turn on the LED and set brightness + brightness
		CMD_start();
		CMD_write(BRIGHTNESS);
		CMD_stop();

	}
}

void TMx_printNum(uint16_t nm)
{
	// Possible decimal values
	const uint8_t deciVal[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

	// This below logic separates the decimal number into 4 digits
	uint8_t d1Digit = nm/1000;
	uint8_t d2Digit = (nm-(d1Digit*1000))/100;
	uint8_t d3Digit = ((nm-(d1Digit*1000))-(d2Digit*100))/10;
	uint8_t d4Digit = (((nm-(d1Digit*1000))-(d2Digit*100))-(d3Digit*10))/1;

	// Initialize the CLK and DIO pins
	__init__TM();

	CMD_start();
	CMD_write(0x44);
	CMD_stop();

	CMD_start();
	CMD_write(0xC0);
	CMD_write(deciVal[d1Digit]);
	CMD_stop();
	CMD_start();
	CMD_write(0xC1);
	CMD_write(deciVal[d2Digit]);
	CMD_stop();

	CMD_start();
	CMD_write(0xC2); // command-2
	CMD_write(deciVal[d3Digit]);
	CMD_stop();
	CMD_start();
	CMD_write(0xC3); // command-2
	CMD_write(deciVal[d4Digit]);
	CMD_stop();

	// Command- Turn on the LED and set brightness + brightness
	CMD_start();
	CMD_write(BRIGHTNESS);
	CMD_stop();

}

void TMx_setBrightness(uint8_t lvl)
{

	// Possible brightness levels
	const uint8_t bLvl[] = {0x88, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F};

	if( (lvl >= 0) && (lvl <= 8) ){
		
		// Assign the BRIGHTNESS level
		BRIGHTNESS = bLvl[lvl];
	}

	// Initialize the CLK and DIO pins
	__init__TM();

	// Command- Turn on the LED and set brightness + brightness
	CMD_start();
	CMD_write(BRIGHTNESS);
	CMD_stop();
}

void editBrightness(uint8_t b)
{
	Bri = b;

	if(Bri == 0){

		turnOnAutoB();
	
	}else if( (Bri > 0) && (Bri <= 8) ){

		turnOffAutoB();
		TMx_setBrightness(Bri);
	}

	eep_Write(DBRI, Bri);
}

void initBri()
{
	Bri = eep_Read(DBRI);
	editBrightness(Bri);
}

// set Brightness absract
void setBrightness()
{
	TMx_printText("-Br-");
	_delay_ms(500);

	if(Bri != 0)
	{
		TMx_printNum(Bri);
		TMx_setBrightness(Bri);

	}else{

		TMx_printText("Auto");
	}
}

void incBri()
{
	Bri += 1;
	if(Bri == 9){

		Bri = 0;
	}

	if(Bri != 0)
	{
		turnOffAutoB();

		TMx_printNum(Bri);
		TMx_setBrightness(Bri);


	}else if(Bri == 0){

		TMx_printText("Auto");
		turnOnAutoB();
	}
	eep_Write(DBRI, Bri);
}

void decBri()
{
	if(Bri != 0){

		Bri -= 1;
	}
	if(Bri == 0){

		Bri = 8;
	}
	
	if(Bri != 0){ turnOffAutoB(); }
	
	TMx_printNum(Bri);
	TMx_setBrightness(Bri);
	eep_Write(DBRI, Bri);
}

