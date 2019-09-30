/*
 * GccApplication2.c
 *
 * Created: 9/30/2019 12:34:51 PM
 * Author : Henry
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>


int main(void)
{
	DDRC &= ~(1 << 3);
	DDRB |= (1 << 2);
	PORTC |= (1 << 3);
	PORTB &= ~(1 << 2);
	
    while (1) 
    {
		if (!(PINC & (1 << 3)))
		{
			PORTB |= (1 << 2);
			_delay_ms(1333);
			PORTB &= ~(1 << 2);
		}
		else
			PORTB &= ~(1 << 2);
    }
	
	return 1;
}

