; for dls148 start time: Wed Dec  5 22:13:57 2012
pop symbol table level: 3
symbol table:
next: 0x106100c40 token: INT value: 3 address: 0xf mask: 0x0 level: 3 length: 2 buffer: i
next: 0x106100b90 token: INT value: 2 address: 0xe mask: 0x0 level: 2 length: 2 buffer: i
next: 0x106100aa0 token: INT value: 1 address: 0xd mask: 0x0 level: 1 length: 2 buffer: i
next: 0x0 token: INT value: 0 address: 0xc mask: 0x0 level: 0 length: 2 buffer: i
symbol table free:
pop symbol table level: 2
symbol table:
next: 0x106100b90 token: INT value: 2 address: 0xe mask: 0x0 level: 2 length: 2 buffer: i
next: 0x106100aa0 token: INT value: 1 address: 0xd mask: 0x0 level: 1 length: 2 buffer: i
next: 0x0 token: INT value: 0 address: 0xc mask: 0x0 level: 0 length: 2 buffer: i
symbol table free:
next: 0x0 token: INT value: 3 address: 0xf mask: 0x0 level: 3 length: 2 buffer: i
pop symbol table level: 1
symbol table:
next: 0x106100aa0 token: INT value: 1 address: 0xd mask: 0x0 level: 1 length: 2 buffer: i
next: 0x0 token: INT value: 0 address: 0xc mask: 0x0 level: 0 length: 2 buffer: i
symbol table free:
next: 0x106100cf0 token: INT value: 2 address: 0xe mask: 0x0 level: 2 length: 2 buffer: i
next: 0x0 token: INT value: 3 address: 0xf mask: 0x0 level: 3 length: 2 buffer: i
Debug: yacc tuples
next: 0x106100ae0 instr: mov value: 0 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x106100a30 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 2 buffer: i
next: 0x106100b60 instr: label value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 5 buffer: main
next: 0x106100bd0 instr: mov value: 1 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x106100c10 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 1 length: 2 buffer: i
next: 0x106100c80 instr: mov value: 2 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x106100cc0 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 2 length: 2 buffer: i
next: 0x106100d30 instr: mov value: 3 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x0 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 3 length: 2 buffer: i
Debug: code tuples
next: 0x106100ae0 instr: mov value: 0 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x106100b20 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 2 buffer: i
next: 0x106100d70 instr: mov value: 0 address: 0x0 mask: 0xc MASK_LABEL MASK_W_REG level: 0 length: 7 buffer: PORTA
next: 0x106100db0 instr: call value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 6 buffer: main
next: 0x106100df0 instr: goto value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 7 buffer: mloop
next: 0x106100a30 instr: return value: 0 address: 0x0 mask: 0x20 MASK_INSTR level: 0 length: 0 buffer: 0x0
next: 0x106100b60 instr: label value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 0 length: 5 buffer: main
next: 0x106100bd0 instr: mov value: 1 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x106100c10 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 1 length: 2 buffer: i
next: 0x106100c80 instr: mov value: 2 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x106100cc0 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 2 length: 2 buffer: i
next: 0x106100d30 instr: mov value: 3 address: 0x0 mask: 0x1 MASK_VALUE level: 0 length: 0 buffer: 0x0
next: 0x0 instr: mov value: 0 address: 0x0 mask: 0x4 MASK_LABEL level: 3 length: 2 buffer: i
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
i_ EQU 0xc
;symbol table free:
i_1 EQU 0xd
i_2 EQU 0xe
i_3 EQU 0xf
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
	movwf	i_
	movf	PORTA,w
	call	main
	goto	mloop
	return
main:
	movlw	0x01
	movwf	i_1
	movlw	0x02
	movwf	i_2
	movlw	0x03
	movwf	i_3
	return	; if main does not have a return
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
symbol table:
next: 0x0 token: INT value: 0 address: 0xc mask: 0x0 level: 0 length: 2 buffer: i
symbol table free:
next: 0x106100c40 token: INT value: 1 address: 0xd mask: 0x0 level: 1 length: 2 buffer: i
next: 0x106100cf0 token: INT value: 2 address: 0xe mask: 0x0 level: 2 length: 2 buffer: i
next: 0x0 token: INT value: 3 address: 0xf mask: 0x0 level: 3 length: 2 buffer: i
