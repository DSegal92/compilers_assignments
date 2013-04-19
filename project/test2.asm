; for dls148 start time: Wed Dec  5 21:48:53 2012
Debug: yacc tuples
next: 0x10c200ae0 instr: mov value: 2 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x0 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 2 buffer: c
Debug: code tuples
next: 0x10c200ae0 instr: mov value: 2 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x10c200a30 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 2 buffer: c
next: 0x0 instr: goto value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 7 buffer: mloop
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
c_ EQU 0xc
;symbol table free:
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
	movwf	c_
	goto	mloop
	return	; if main does not have a return
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
symbol table:
next: 0x0 token: CHAR value: 2 address: 0xc mask: 0x0 level: 0 length: 2 buffer: c
symbol table free:
