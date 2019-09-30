;
; DA2A.asm
;
; Created: 9/29/2019 3:41:36 PM
; Author : Henry M
;
/* This program is design to turn "ON" and "OFF" a signal
 out of Port B.3 with a 40% duty cycle and a period of 625ms 
 forever */
 .include "m328pbdef.inc"

	SBI DDRB, 3				;SET BIT 3 IN PORTB TO OUTPUT
L1:
	SBI PORTB, 3			;SEND TO PORTB VALUE OF 1 = ON
CALL delay250ms				;DELAY OF 250ms
	CBI PORTB, 3			;SEND TO PORTB VALUE OF 0 = 0FF
CALL delay375ms				;DELAY OF 375ms
	 JMP L1 
;--------------------------------------------------------------------------
delay250ms:
	ldi R19, 11
d0: ldi R20, 255
d1:	ldi R21, 237
d2:	dec R21
	brne d2 //if R21 != 0 go to delay2 label
	dec R20
	brne d1 //if R20 != 0 go to delay1 label
	dec R19
	brne d0 //if R19 != 0 go to delay0
	ret
;----------------------------------------------------------------------------
delay375ms:
	ldi R19, 12
s0: 
	ldi R20, 254
s1:	
	ldi R21, 245
s2:	
	ldi r22, 255
	dec r21
	brne s2 //if R21 != 0 go to delay2 label
	dec R20
	brne s1 //if R20 != 0 go to delay1 label
	dec R19
	brne s0 //if R19 != 0 go to delay0	
	ldi r23,255
s3: 
	nop
	nop	
	dec r22
	brne s3
	ldi r24,255
s4:
	nop
	nop
	dec r23
	brne s4
s5: 
	nop
	nop
	dec r24
	brne s5
ret
;----------------------------------------------------------------------------