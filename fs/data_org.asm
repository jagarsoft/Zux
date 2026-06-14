;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 22110-51889e5300-20231220
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Sat Mar 08 14:58:55 2025

    MODULE getutil_asm

    INCLUDE "z80_crt0.hdr"

    SECTION	code_compiler

    SECTION	bss_compiler
    SECTION	code_compiler
; --- Start of Optimiser additions ---


; --- Start of Static Variables ---

    SECTION	bss_compiler
._data_org  defw 0xDADA		; 0xDADA is magic number for build
            defs 7*2		; first 8 words of MM, FS, INIT are for stack
._brksize   defw 0 ;	offset dgroup:@END  ; first free memory
._sp_limit  defw 0

    SECTION	code_compiler

; --- Start of Scope Defns ---

    GLOBAL	_data_org
    GLOBAL	_brksize
    GLOBAL	_sp_limit

; --- End of Scope Defns ---


; --- End of Compilation ---