/*
 * Assignment_2C_PART_C.c
 *
 * Created: 10/14/2019 11:09:57 PM
 * Author : Henry M
 *	THIS PROGRAM WILL USE TIMER 0 - CTC MODE
 *	TO CREATE A TIME DELAY OF 10MS WITH AN INTERRUPT
 */
 #define F_CPU 16000000UL

 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>

 int main(void)
 {
 DDRB |= (1 << DDB5);		//set PORTB.5 as output
 TCCR0A |= (1 << WGM01);		//set timer control CTC
 TIMSK0 |= (1 << OCIE0A);	//set interrupt on compare match
 TCCR0B |= 0x05;				//PS = 1024
 OCR0A = 156;				//load compare reg value
 sei();						//set global interrupt
 while (1)
 {
 }
 }
 ISR (TIMER0_COMPA_vect)			//ISR
 {
 PORTB ^= (1 << 5);			//toggle PORTB.5
 }
