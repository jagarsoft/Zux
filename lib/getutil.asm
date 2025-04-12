;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 22110-51889e5300-20231220
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Sat Mar 08 14:58:55 2025

    MODULE getutil_asm

    INCLUDE "z80_crt0.hdr"

    SECTION	code_compiler

._get_base
        ld      hl, 0
        ret

._get_size
        ld      hl, 0
        ret

._get_tot_mem
        ld      hl, 2
        ret

    SECTION	bss_compiler
	SECTION	code_compiler
; --- Start of Optimiser additions ---


; --- Start of Static Variables ---

	SECTION	bss_compiler
	SECTION	code_compiler


; --- Start of Scope Defns ---

	GLOBAL	_get_base
	GLOBAL	_get_size
	GLOBAL	_get_tot_mem


; --- End of Scope Defns ---


; --- End of Compilation ---