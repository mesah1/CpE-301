/*
 * Assignment_2C_PART_B.c
 *
 * Created: 10/14/2019 9:46:41 PM
 * Author : Henry M
 *	THIS PROGRAM WILL USE TIMER 1 - NORMAL MODE
 *	TO CREATE A TIME DELAY OF 1MS WITH AN INTERRUPT 
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= (1 << DDB5);		//set PORTB.5 as output
	TCCR0A = 0;					//set timer control 
	TCCR0B |= 0x05;				//PS = 1024
	TCNT0 = 248;				//load value
	TIMSK0 = (1 << TOIE0);		//time capture
	sei();						//set global interrupt
	
	while (1)
	{
	}
}
ISR (TIMER0_OVF_vect)			//ISR
{
	PORTB ^= (1 << 5);			//toggle PORTB.5
	TCNT0 = 248;				//reset value
}
