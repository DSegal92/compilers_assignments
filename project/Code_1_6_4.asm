; for dls148 start time: Wed Dec  5 22:28:00 2012
; automatic code generation for PIC16F84A
; EECS337 Compiler Design
; by: dls148, date: Fall 2012
; for PIC16F84A processor
; CPU configuration
; (16F84 with RC osc, watchdog timer off, power-up timer on)
	processor 16f84A
	include <p16F84A.inc>
	__config _RC_OSC & _WDT_OFF & _PWRTE_ON
;symbol table:
x_ EQU 0xc
;symbol table free:
x_1 EQU 0xd
; power-up or reset vector
	org	0x00	; on reset PC set to 0x00
reset:			
	goto	init	; skip interrupt vector space (reserved)
; interrupt vector 
	org 	0x04
inter:		; on interrupt PC set to 0x04 and automatically clears GIE
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
; here begins the main program
	movlw	0x02
	movwf	x_
	movf	PORTA,w
	call	main
	goto	mloop
	return
b_:
	movlw	0x01
	addwf	x_,w
	movwf	x_
	movlw	0x25
	call	printf
	movlw	0x64
	call	printf
	movlw	0x5c
	call	printf
	movlw	0x6e
	call	printf
	movlw	0x00
	call	printf
	movf	x_,w
	call	printf
	return
c_:
	movlw	0x01
	movwf	x_1
	movlw	0x25
	call	printf
	movlw	0x64
	call	printf
	movlw	0x5c
	call	printf
	movlw	0x6e
	call	printf
	movlw	0x00
	call	printf
	movlw	0x01
	call	printf
	addwf	x_1,w
	call	printf
	return
main:
	call	b_
	call	c_
	retlw	0x00
	return	; if main does not have a return
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
