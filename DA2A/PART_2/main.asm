;
; DA2A_P2.asm
;
; Created: 9/29/2019 7:09:12 PM
; Author : Henry M
/* This program will read the input from a switch connected 
to PINC.3 and will turn an LED connected to PORTB.2 for 1.333s */
.include "m328pbdef.inc"

	CBI DDRC, 3			;CLEAR BIT 3 PIN C FOR INPUT
	SBI DDRB, 2			;SET BIT 2 PORT B FOR OUTPUT
	SBI PORTC, 3		;SET PULL-UP IN BIT 3 PINC	TO READ SWITCH	
	CBI PORTB, 2		;SET PORTB.2 TO "OFF"
CHECK:
	SBIC PINC, 3		;SKIP NEXT IF PINC.3 IS CLEAR
	JMP CHECK			;LOOPS AS LONG AS PINC.3 IS HIGH
	SBI	PORTB, 2		;SET OUTPUT IN PORTB.2 TO "ON"
CALL delay1333ms
	CBI PORTB, 2		;SET OUTPUT "OFF" AFTER DELAY
	JMP CHECK			;GO BACK TO CHECK 
;------------------------------------------------------------------------
delay1333ms:
	ldi R19, 55
d0: ldi R20, 255
d1:	ldi R21, 252
d2: dec R21
	brne d2 //if R21 != 0 go to delay2 label
	nop
	dec R20
	brne d1 //if R20 != 0 go to delay1 label
	dec R19
	brne d0 //if R19 != 0 go to delay0
	ldi r22,255
d3: nop
	nop
	nop
	nop
	nop
	dec r22
	brne d3
	ldi r23,255
d4: nop
	nop
	nop
	nop
	nop
	dec r23
	brne d4
	ldi r24, 255
d5: nop
	nop
	nop
	nop
	nop
	dec r24
	brne d5
ret
;--------------------------------------------------------------------------------