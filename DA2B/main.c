/*
 * INTERRUPT.c
 *
 * Created: 10/4/2019 10:14:03 PM
 * Author : Henry M
 * This program will read the input from an interrupt connected
*  to PIND.2(INT0) and will toggle an LED connected to PORTB.5 
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
	DDRB |= (1 << 5);		//set bit 5 in PORTB to output
	PORTD |= (1 << 2); 		//pull-up activated
	EICRA = 0x2;			//falling edge triggered
	EIMSK = (1 << INT0);	//enable external INT0
	sei();					//enable global interrupts
		
	PORTB &= (0 << 5);		//set PORTB.2 "OFF"
	
	while (1)				//wait here for interrupt to happen
	{

	}
}

ISR (INT0_vect)	//ISR FOR EXTERNAL INTERRUPT 0
{
	PORTB ^= (1 << 5);  //when detected toggle PORTB.2 for 1s
	_delay_ms(1000);
}	




