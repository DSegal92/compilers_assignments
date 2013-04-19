; ar.asm raw quads
; main() { char a = 2; char b = a - 3; return 0; }
; t1 = 2
; a = t1
; t2 = a
; t3 = 3
; t4 = t2 - t3
; b = t4
; EECS337 Compiler Design
; by: dls148, date: Fall 2012
; for PIC16F84A processor
; CPU configuration
; (16F84 with RC osc, watchdog timer off, power-up timer on)
	processor 16f84A
	include <p16F84A.inc>
	__config _RC_OSC & _WDT_OFF & _PWRTE_ON
a_ equ 0x0c
b_ equ 0x0d
t1 equ 0x0e
t2 equ 0x0f
t3 equ 0x10
t4 equ 0x11
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
	movwf t1
	movf t1, W
	movwf a_
	movf a_, W
	movwf t2
	movlw 3
	movwf t3
	movf t3, W
	subwf t2, W
	movwf t4
	movf t4, W
	movwf b_
	retlw	0x00
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
