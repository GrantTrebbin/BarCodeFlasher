/*
 * BarCodeFlasher.c
 *
 * Created: 1/06/2014 8:58:15 PM
 *  Author: GPT
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

// bit manipulation macros
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x) (0x01 << (x))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x)) 

volatile unsigned int patternChar;
volatile unsigned char patternBit;
volatile char pattern[] = {0x00, 0x69, 0x0D, 0xC5, 0x64, 0x2F, 0x24, 0xF4, 0xF4, 0x5E, 0xEA, 0x73, 0x67, 0x2C, 0xB9, 0xEB, 0xB1, 0xD6, 0x00};


ISR(TIMER1_COMPA_vect) {
	
	if( bit_get(pattern[patternChar], BIT(patternBit-1)) == 0x00 ){
		PORTD = 0xFF;
	}else{
		PORTD = 0x00;
	}		

	patternBit--;
	if (patternBit == 0){
		patternBit = 8;
		patternChar++;
	}
	if (patternChar == 19) patternChar = 0;
	
} 

void timer1_initialize(void){
	//Timer1 initialization
	bit_set(TCCR1B,BIT(CS10));
	bit_clear(TCCR1B,BIT(CS11));
	bit_clear(TCCR1B,BIT(CS12));
	bit_set(TIMSK,BIT(OCIE1A));
	
	bit_clear(TCCR1A,BIT(WGM10));
	bit_clear(TCCR1A,BIT(WGM11));
	bit_set(TCCR1B,BIT(WGM12));
	bit_clear(TCCR1B,BIT(WGM13));
	
	TCNT1 = 0;
	OCR1A = 0x0160;
}

int main(void)
{
	patternChar = 0;
	patternBit = 8;	
	timer1_initialize();

	DDRB = 0xFF;
	DDRD = 0xFF;
	sei();
		
	
		
	while(1)
	{

	}
}
