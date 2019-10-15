/*
 * Assignment_2C_PART_A.c
 *
 * Created: 10/14/2019 6:16:20 PM
 * Author : Henry M
 *	THIS PROGRAM WILL USE TIMER 0 - NORMAL MODE
 *	TO CREATE A TIME DELAY OF 10ms
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << DDB5);	//set PORTB.5 as output
	TCCR0A = 0;			//normal operation
	TCCR0B |= (1 << CS02) | (1 << CS00); //PS = 1024
	TCNT0 = 99.75;		//counter preset value = 99.75 
	
	PORTB &= ~(1 << DDB5);
    while (1) 
    {
		//wait for overflow event
		while ((TIFR0 & 0x01)==0); 
		PORTB ^= (1 << DDB5 );
		TCNT0 = 99.75;	//counter preset value = 99.75
		TIFR0 = 0x01;	//reset the overflow flag
		
    }
}
