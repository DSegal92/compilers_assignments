; br.asm raw quads
; main() { char a; char b[ 10]; b[4] = 1; a = b[4]; return 0; }
; t1 = 4
; b[ t1] = 1
; t2 = 4
; t3 = b[ t2]
; a = t3
; EECS337 Compiler Design
; by: dls148, date: Fall 2012
; for PIC16F84A processor
; CPU configuration
; (16F84 with RC osc, watchdog timer off, power-up timer on)
	processor 16f84A
	include <p16F84A.inc>
	__config _RC_OSC & _WDT_OFF & _PWRTE_ON
a_ EQU  0x0c
b_ EQU  0x0d
t1 EQU	0x17
t2 EQU	0x18
t3 EQU	0x19
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
	movlw 4
	movwf t1
	movf t1, W
	addlw b_
	movwf FSR
	movlw 1
	movwf INDF
	movlw 4
	movwf t2
	movf t2, W
	addlw b_
	movwf FSR
	movf INDF, W
	movwf t3
	movf t3, W
	movwf a_
	retlw	0x00
; only standard library function
printf:			
	movwf	PORTB	; output w to standard output (stdout)
	return
	end		; end of program code
