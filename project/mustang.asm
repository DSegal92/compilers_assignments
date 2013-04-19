; for dls148 start time: Wed Dec  5 22:59:57 2012
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
count EQU 0xe
index EQU 0xd
lights EQU 0xc
;symbol table free:
flags_1 EQU 0xf
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
	movlw	0x00
	movwf	lights
	movlw	0x00
	movwf	index
	movlw	0x00
	movwf	count
	movf	PORTA,w
	call	main
	goto	mloop
	return
delay:
	movlw	0xff
	movwf	index
label2:
	movf	index,w
	btfsc	0x03,2
	goto	label3
	movlw	0x01
	subwf	index,w
	movwf	index
	movlw	0xff
	movwf	count
label0:
	movf	count,w
	btfsc	0x03,2
	goto	label1
	movlw	0x01
	subwf	count,w
	movwf	count
	goto	label0
label1:
	goto	label2
label3:
	return
clear:
	movlw	0x00
	movwf	lights
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
	movf	lights,w
	call	printf
	call	delay
	return
left:
	movlw	0x00
	subwf	lights,w
	btfsc	0x03,2
	goto	label8
	movlw	0x10
	movwf	lights
	goto	label9
label8:
	movlw	0x10
	subwf	lights,w
	btfsc	0x03,2
	goto	label6
	movlw	0x30
	movwf	lights
	goto	label7
label6:
	movlw	0x30
	subwf	lights,w
	btfsc	0x03,2
	goto	label4
	movlw	0x70
	movwf	lights
	goto	label5
label4:
	movlw	0x00
	movwf	lights
label5:
label7:
label9:
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
	movf	lights,w
	call	printf
	call	delay
	return
right:
	movlw	0x00
	subwf	lights,w
	btfsc	0x03,2
	goto	label14
	movlw	0x08
	movwf	lights
	goto	label15
label14:
	movlw	0x08
	subwf	lights,w
	btfsc	0x03,2
	goto	label12
	movlw	0x0c
	movwf	lights
	goto	label13
label12:
	movlw	0x0c
	subwf	lights,w
	btfsc	0x03,2
	goto	label10
	movlw	0x0e
	movwf	lights
	goto	label11
label10:
	movlw	0x00
	movwf	lights
label11:
label13:
label15:
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
	movf	lights,w
	call	printf
	call	delay
	return
hazard:
	movlw	0x00
	subwf	lights,w
	btfsc	0x03,2
	goto	label16
	movlw	0x7e
	movwf	lights
	goto	label17
label16:
	movlw	0x00
	movwf	lights
label17:
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
	movf	lights,w
	call	printf
	call	delay
	return
main:
	movwf	flags_1
label24:
	movlw	0x01
	btfsc	0x03,2
	goto	label25
	movlw	0x01
	andwf	flags_1,w
	btfsc	0x03,2
	goto	label22
	call	hazard
	goto	label23
label22:
	movlw	0x02
	andwf	flags_1,w
	btfsc	0x03,2
	goto	label20
	call	left
	goto	label21
label20:
	movlw	0x04
	andwf	flags_1,w
	btfsc	0x03,2
	goto	label18
	call	right
	goto	label19
label18:
	call	clear
label19:
label21:
label23:
	goto	label24
label25:
	retlw	0x00
	return	; if main does not have a return
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
