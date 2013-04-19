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
;symbol table free:
w_1 EQU 0xc
x_1 EQU 0xd
y_1 EQU 0xe
z_1 EQU 0xf
i_1 EQU 0x10
j_1 EQU 0x11
i_2 EQU 0x12
j_2 EQU 0x12
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
	movf	PORTA,w
	call	main
	goto	mloop
	return
main:
	movwf	w_1
	movwf	x_1
	movwf	y_1
	movwf	z_1
	movlw	0x04
	movwf	i_1
	movlw	0x05
	movwf	j_1
	movlw	0x07
	movwf	j_2
	movlw	0x06
	movwf	i_1
	movf	j_2,w
	addwf	i_1,w
	movwf	w_1
	movf	j_1,w
	addwf	i_1,w
	movwf	x_1
	movlw	0x08
	movwf	i_2
	movf	j_1,w
	addwf	i_2,w
	movwf	y_1
	movf	j_1,w
	addwf	i_1,w
	movwf	z_1
	movlw	0x77
	call	printf
	movlw	0x3a
	call	printf
	movlw	0x25
	call	printf
	movlw	0x64
	call	printf
	movlw	0x2c
	call	printf
	movlw	0x5c
	call	printf
	movlw	0x74
	call	printf
	movlw	0x78
	call	printf
	movlw	0x3a
	call	printf
	movlw	0x25
	call	printf
	movlw	0x64
	call	printf
	movlw	0x2c
	call	printf
	movlw	0x5c
	call	printf
	movlw	0x74
	call	printf
	movlw	0x79
	call	printf
	movlw	0x3a
	call	printf
	movlw	0x25
	call	printf
	movlw	0x64
	call	printf
	movlw	0x2c
	call	printf
	movlw	0x5c
	call	printf
	movlw	0x74
	call	printf
	movlw	0x7a
	call	printf
	movlw	0x3a
	call	printf
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
	movf	w_1,w
	call	printf
	movf	x_1,w
	call	printf
	movf	y_1,w
	call	printf
	movf	z_1,w
	call	printf
	retlw	0x00
	return	; if main does not have a return
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
