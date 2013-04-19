; cr.asm raw quads
; main() { char a = 2; if( a ) a = a + 1; else a = a - 1; return 0; }
;	t1 = 2
; 	a = t1
; 	iftrue t2 goto label1
; 	t3 = a
;	t4 = 1
;	t5 = t3 + t4
;	a = t5
; 	goto label2
; label1:
;	t6 = a
;	t7 = 1
;	t8 = t6 - t7
;	a = t8
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
t1 EQU  0x0d
t2 EQU  0x0e
t3 EQU  0x0f
t4 EQU  0x10
t5 EQU  0x11
t6 EQU  0x12
t7 EQU  0x13
t8 EQU  0x14
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
	movf t2, F
	btfsc STATUS, Z
	goto label1
	movf a_, W
	movwf t3
	movlw 1
	movwf t4
	movf t4, W
	addwf t3, W
	movwf t5
	movf t5, W
	movwf a_
	goto label2
label1:
	movf a_, W
	movwf t6
	movlw 1
	movwf t7
	movf t7, W
	addwf t6, W
	movwf t8
	movf t8, W
	movwf a_
label2:
	retlw	0x00
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
