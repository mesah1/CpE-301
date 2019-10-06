;
; EXT_INT0_IRQ.asm
;
; Created: 10/5/2019 6:03:27 PM
; Author : Henry M
;
;* This program will read the input from an interrupt connected
;*  to PIND.2(INT0) and will toggle an LED connected to PORTB.2 
;
.include "m328pbdef.inc"

.ORG 0			;reset
JMP MAIN
.ORG 0x05		;location of external interrupt
JMP EX0_ISR
MAIN:
	LDI R16, HIGH(RAMEND)
	OUT SPH, R16
	LDI R20, LOW(RAMEND)
	OUT SPL, R16	;initilaize stack

	LDI R16, 2		;falling edge triggered
	STS EICRA,R20
	SBI DDRB, 5		;set bit 5 in PORTB as output
	SBI PORTD, 2	;pull-up activated 
	LDI R16, 1 << INT0	;enable interrupt INT0
	OUT EIMSK, R16
	SEI					;enable global interrupts
HERE: JMP HERE
;----------------------------------------------------------------------
EX0_ISR:
	IN R17, PORTB
	LDI R18, (1 << 5) ;toggle PORTB.5
	EOR R17, R18
	OUT PORTB, R17
	CALL DELAY
	RETI
;-----------------------------------------------------------------------
DELAY:				;1.333 s delay
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


