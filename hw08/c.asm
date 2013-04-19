; c.asm
; main() { char a = 2; if( a ) a = a + 1; else a = a - 1; return 0; }
; 	a = 2
; 	iftrue a goto label1
; 	a = a + 1
; 	goto label2
; label1:
;	a = a - 1
; label2:
; EECS337 Compiler Design
; by: dls148, date: Fall 2012
; for PIC16F84A processor
; CPU configuration
; (16F84 with RC osc, watchdog timer off, power-up timer on)
	processor 16f84A
	include <p16F84A.inc>
	__config _RC_OSC & _WDT_OFF & _PWRTE_ON
a_ EQU  0x0c
; power-up or reset vector
	org	0x00	; on reset PC set to 0x00
reset:			
	goto	init	; skip interrupt vector space (reserved)
; interrupt vector 
	org 	0x04
inter:			; on interrupt PC set to 0x04 and automatically clears GIE
	retfie		; return from interrupt and automatically sets GIE
; beginning of program code
	org	0x08
init:
; On reset all ports are inputs.
	bsf	STATUS,RP0	; switch to bank 1 memory
	clrf	TRISA		; set PORTA to all outputs
	clrf	TRISB		; set PORTB to all outputs
	bcf	STATUS,RP0	; return to bank 0 memory
mloop:
; read from the standard input (stdin)
	movf	PORTA,w
	call	main
	goto	mloop
; here begins the main program 
main:
	movlw 2
	movwf a_
	movf a_, F
	btfsc STATUS, Z
	goto label1
	incf a_, F
	goto label2
label1:
	decf a_, F
label2:
	retlw	0x00
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
