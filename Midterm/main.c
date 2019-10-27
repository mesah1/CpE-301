/*
 * Midterm.c
 *
 * Created: 10/26/2019 2:06:31 PM
 * Author : Henry Mesa
 * TOOL: LM35, EXPLAINED-MINI(ATMEGA328PB), ESP01
 * THIS CODE WILL UPLOAD TEMPERATURE VALUES TO THINGSPEAK.COM THROUGHT USART
 *	
 */ 

#define F_CPU 16000000UL
#define UBRR_9600 103

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

//Function declaration
void read_adc(void);
void adc_init(void);
void USART_init( );
void USART_tx_string(char *data);


volatile float adc;
char ar[255];

int main(void)
{
	adc_init();					//intialize ADC
	read_adc();
	USART_init(UBRR_9600);			//initialize USART
	USART_tx_string("Connected!\n");	
	snprintf(ar, sizeof(ar),"%f\n\r",adc/128);	//print 
	USART_tx_string(ar);
		
    while (1) 
    {
	
    }
}
/* INITIALIZING ADC */
void adc_init(void){
	//ADC ENABLE AND SET-UP
	ADMUX = (0 << REFS1)|    // external cap at AREF
	(1 << REFS0)|    // AVcc -  Reference Selection INTERNAL
	(1 << ADLAR)|    // ADC Left Adjust Result
	(1 << MUX2)|     // Analog Channel Selection Bits
	(0 << MUX1)|     // ADC0 (PC5 PIN28)
	(1 << MUX0);
	ADCSRA = (1 << ADEN)|    // ADC ENable
	(0 << ADSC)|     // ADC Start Conversion
	(0 << ADATE)|    // ADC Auto Trigger Enable
	(0 << ADIF)|     // ADC Interrupt Flag
	(0 << ADIE)|     // ADC Interrupt Enable
	(1 << ADPS2)|    // ADC Prescaler 
	(0 << ADPS1)|
	(1 << ADPS0);
	
	// Timer/Counter1 Interrupt Mask Register
	TIMSK1 |= (1<<TOIE1); // enable interrupt flag
	// Set Prescalar
	TCCR1B = 5; // setting the prescalar to 1024
	// Set timer
	TCNT1 = 7000; // set TCNT1

	_delay_ms(1000); // wait a bit
	sei(); //interrupt
}
/* READ ADC PINS */
void read_adc(void){
   unsigned char i = 4;
   adc = 0;
   while (i--)
   {
	   ADCSRA |= (1 << ADSC);
	   while(ADCSRA & (1 << ADSC));
	   adc+= ADC;
	   _delay_ms(50);
   }
   adc = adc / 4;  // Average a few samples	
}
/* INITIALIZING USART (RS-232) */
void USART_init(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0)|(1 << RXEN0)| ( 1 << RXCIE0); //transreciver enabled and RX interrupt
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //5-bit characters 
}
/* SEND STRING TO RS-232 */
void USART_tx_string(char *data){
	while ((*data != '\0')){
		while (!(UCSR0A & (1 << UDRE0)));
			UDR0 = *data;
		data++;
	}
}
void UART_sendString(volatile unsigned char AT[]){
	volatile unsigned char len = 0;
	volatile unsigned char i;
	
	while (AT[len] != 0){
		len++;
	}
	for (i = 0x00; i < len; i++)
	{
		//Wait for the transmitter to finish
		while (!(UCSR0A & (1 << UDRE0)))
		{
			UDR0 = AT[i];
		}
	}
}
ISR(TIMER1_OVF_vect){

	unsigned char AT_COMMMANDS[] = "AT\n\r"; //AT Commands
	unsigned char CWMODE[] ="AT+CWMODE=1\n\r"; //Set the mode
	unsigned char CWJAP[] ="AT+CWJAP=\"SSID\",\"PASSWORD\"\r\n"; // WIFI username and password
	unsigned char CIPMUX[] ="AT+CIPMUX=0\n\r";
	unsigned char CIPSTART[] ="AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\n\r";
	unsigned char CIPSEND[] ="AT+CIPSEND=51\n\r";
	unsigned char DATA[]="GET  /update?api_key=0DSHG7MOCFW2VGFI&field1=";
	unsigned char CLOSE[]="AT+CIPCLOSE\n\r";
	
	read_adc();
	snprintf(ar, sizeof(ar),"%f\n\r",adc/128);	//print 

	
	UART_sendString(AT_COMMMANDS);
	_delay_ms(3000);
	UART_sendString(CWMODE);
	_delay_ms(2000);
	UART_sendString(CWJAP);
	_delay_ms(3000);
	UART_sendString(CIPMUX);
	_delay_ms(2000);
	UART_sendString(CIPSTART);
	_delay_ms(3000);
	UART_sendString(CIPSEND);
	_delay_ms(3000);
	UART_sendString(DATA);
	UART_sendString(ar);
	_delay_ms(3000);
	UART_sendString(CLOSE);
	_delay_ms(2000);

	
	USART_tx_string(ar);	
					
	TCNT1 = 7000; //resets timer
}
