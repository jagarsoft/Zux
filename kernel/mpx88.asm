            ; MODULE	mpx88_asm

            ; include the following	from kernel/const.h
            defc K_STACK_BYTES  = 256
            defc IDLE           = -999
            defc NR_REGS        = 6

            defc HL_REG         = 6
            defc DE_REG         = 4
            defc BC_REG         = 2

            ; include the following	from ../h/com.h
            ;DISKINT		EQU  1
            defc CLOCK		= -3
            defc CLOCK_TICK	=  2
            ;FLOPPY		EQU -5

            EXTERN  _proc_ptr
            EXTERN  _cur_proc
            EXTERN  _k_stack
            EXTERN  _int_mess

            EXTERN  _keyboard
            EXTERN  _sys_call
            EXTERN  _interrupt

            PUBLIC  _s_call
            PUBLIC  _tty_int
            PUBLIC  _clock_int
            PUBLIC  _restart

;===========================================================================
;				s_call
;===========================================================================

_s_call:    ; System calls are vectored here.
            call    save    ; save the machine state

            ld      d, 0
            ; prepare to call
            ; void sys_call(int function, int caller, int src_dest, struct message* m_ptr)
            ld      hl, (_proc_ptr)
            ld      e, BC_REG
            add     hl, de
            ld      c, (hl)
            inc     hl
            ld      b, (hl)
            push    bc  ; push(SEND/RECEIVE/BOTH) (was bc)
            ld      hl, (_cur_proc)
            push    hl  ; push caller
            ld      hl, (_proc_ptr)
            ld      e, DE_REG
            add     hl, de
            ld      c, (hl)
            inc     hl
            ld      b, (hl)
            push    bc  ; push(src/dest) (was de)
            ld      hl, (_proc_ptr)
            ld      e, HL_REG
            add     hl, de
            ld      c, (hl)
            inc     hl
            ld      b, (hl)
            push    bc  ; push(pointer to user message)	(was hl)

            call    _sys_call
            jp      _restart

;===========================================================================
;				tty_int
;===========================================================================

_tty_int:	; Interrupt routine for	terminal input.
            call    save		; save the machine state
            call    _keyboard   ; process a keyboard interrupt
            jp      _restart	; continue execution

;===========================================================================
;				clock_int
;===========================================================================

_clock_int:	; Interrupt routine for	the clock.
            call    save			; save the machine state
            ld      hl, CLOCK		; prepare to push first	parameter
            push    hl  			; push first parameter

            ;ld      ix, _int_mess   ; prepare to call interrupt(CLOCK,&intmess)
	        ;ld      (ix+2), CLOCK_TICK; build	message	for clock task
	        ;push    ix				; push second parameter

	        ld      hl, _int_mess+2   ; prepare to call interrupt(CLOCK,&intmess)
            ld      (hl), CLOCK_TICK; build	message	for clock task
            dec     hl
            dec     hl
            push    hl				; push second parameter

	        call    _interrupt		; this is the call
            jp      _restart		; continue execution

;===========================================================================
;				save
;===========================================================================
.save:      ; save the machine state in the	proc table.
            ; stack: ret_save/rst's ret
            ex      (sp), hl        ; ret_save <-> hl
            ld      (ret_save), hl  ; save hl for later ; we need a	free register
            pop     hl
            ld      (hl_save), hl
            pop     hl
            ld      (rst_save), hl
            ld      (_proc_ptr + (NR_REGS+1)*2), sp ; save sp after &proc.p_reg[NR_REGS]
            ; start	save set up
            ; now use sp to	point into proc	table/task save
            push    de
            ld      hl, (_proc_ptr)
            ld      de, NR_REGS*2
            add     hl, de
            pop     de
            ld      sp, hl  ; sp = &proc.p_reg[NR_REGS]
            ld      hl, (hl_save)

            push    iy      ; start	saving all the registers
            push    ix
            push    hl
            push    de
            push    bc
            push    af      ; all registers now	saved

            ld      de, K_STACK_BYTES
            ld      hl, _k_stack
            add     hl, de
            ; TODO check splimit
            ld      sp, hl

            ld      hl, (ret_save)
            jp      (hl)

;===========================================================================
;				restart
;===========================================================================

_restart:   ; This routine sets up and runs	a proc or task.
            di
            ld      hl, _cur_proc
            ld      de, IDLE
            ld      a, e
            cp      (hl)
            jr      nz, restart_not_IDLE
            inc     hl
            ld      a, d
            cp      (hl)
            jr      z, _idle

.restart_not_IDLE:
            ld      sp, (_proc_ptr)

            pop     af      ; start	restoring registers
            pop     bc
            pop     de
            pop     hl
            pop     ix
            pop     iy

            ld      (hl_save), hl
            ld      sp, (_proc_ptr + (NR_REGS+1)*2) ; restore sp to clean stack
            ld      hl, (hl_save)
            push    hl
            ld      hl, (rst_save)

            ex      (sp), hl        ; hl <-> rst_save

            ei
            ret

;===========================================================================
;				idle
;===========================================================================
_idle:				    ; executed when	there is no work
            ei          ; enable interrupts
.L3:        halt        ; just idle while waiting for interrupt
            jr      L3  ; loop until interrupt

.ret_save:  defs    2
.hl_save:   defs    2
.rst_save:  defs    2