;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 22110-51889e5300-20231220
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Sat Mar 08 14:58:55 2025


        MODULE	sendrec_asm

        INCLUDE "z80_crt0.hdr"

        SECTION	code_compiler

        ; See ../h/com.h for C definitions
        defc    SEND = 1
        defc    RECEIVE = 2
        defc    BOTH = 3
        defc    SYSVEC = 0x20   ; 32

        PUBLIC  _send
_send:
        ld  bc, SEND        ; function
        jr  L0

        PUBLIC  _receive
_receive:
        ld  bc, RECEIVE     ; function
        jr  L0

        PUBLIC  _sendrec
_sendrec:
        ld  bc, BOTH        ; function

.L0:
        pop     af          ; ret
        pop     hl          ; mess ptr
        pop     de          ; src or dest
        push    de          ; copy arg by reg
        push    hl
        push    af

        rst     SYSVEC
        ret

    SECTION	bss_compiler
	SECTION	code_compiler

; --- Start of Optimiser additions ---


; --- Start of Static Variables ---

	SECTION	bss_compiler
	SECTION	code_compiler


; --- Start of Scope Defns ---

	GLOBAL	_send
	GLOBAL	_receive
	GLOBAL	_sendrec


; --- End of Scope Defns ---


; --- End of Compilation ---