/*
 * GccApplication1.c
 *
 * Created: 9/30/2019 12:07:49 PM
 * Author : Henry
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

int main(void)
{
	DDRB |= (1 << 2);		//PORTB.3 AS OUTPUT
	PORTB &= ~(1 << 2);		//OUTPUT "OFF"
	
	while(1){
		
		PORTB &= ~(1 << 2);		//OUTPUT "OFF"
		_delay_ms(375);			//DELAY 375ms @ 16MHz
		PORTB |= (1 << 2);		//OUTPUT "ON"
		_delay_ms(250);			//DELAY 250ms @ 16MHz
	}
	
	return 1;
}

