PUBLIC  _phys_copy
PUBLIC  _cp_mess
PUBLIC  _port_out
PUBLIC  _port_in
PUBLIC  _lock
PUBLIC  _unlock
PUBLIC  _restore
PUBLIC  _build_sig
PUBLIC  _get_chrome

            ; MODULE	klib88_asm

;===========================================================================
;				phys_copy
;===========================================================================
; This routine copies a	block of physical memory.  It is called	by:
;    phys_copy(	(long) source, (long) destination, (long) bytecount)

_phys_copy:
            ret         ; return to caller


;===========================================================================
;				cp_mess
;===========================================================================
; This routine is makes	a fast copy of a message from anywhere in the address
; space	to anywhere else.  It also copies the source address provided as a
; parameter to the call	into the first word of the destination message.
; It is	called by:
;    cp_mess[src, src_clicks, src_offset, dst_clicks, dst_offset]
; where	all 5 parameters are shorts [16-bits].
;
; Note that the	message	size, 'Msize' is in WORDS [not bytes] and must be set
; correctly.  Changing the definition of message the type file and not changing
; it here will lead to total disaster.
; This routine destroys	ax.  It	preserves the other registers.

_cp_mess:
            ret			; that's all folks!


;===========================================================================
;				port_out
;===========================================================================
; port_out(port, value)	writes 'value' on the I/O port 'port'.

_port_out:
            ret			; return to caller


;===========================================================================
;				port_in
;===========================================================================
; port_in(port,	&value)	reads from port	'port' and puts	the result in 'value'.

_port_in:
	        ret			; return to caller


;===========================================================================
;				lock
;===========================================================================
; Disable CPU interrupts.

_lock:
    di          ; disable interrupts
	ret			; return to caller


;===========================================================================
;				unlock
;===========================================================================
; Enable CPU interrupts.

_unlock:
	ei			; enable interrupts
	ret			; return to caller

;===========================================================================
;				restore
;===========================================================================
; Restore enable/disable bit to	the value it had before	last lock.
_restore:
	ret			; return to caller

;===========================================================================
;				build_sig
;===========================================================================
; Build	a structure that is pushed onto	the stack for signals.	It contains
; pc, psw, etc., and is	machine	dependent. The format is the same as generated
; by hardware interrupts, except that after the	"interrupt", the signal	number
; is also pushed.  The signal processing routine within	the user space first
; pops the signal number, to see which function	to call.  Then it calls	the
; function.  Finally, when the function	returns	to the low-level signal
; handling routine, control is passed back to where it was prior to the	signal
; by executing a return-from-interrupt instruction, hence the need for using
; the hardware generated interrupt format on the stack.	 The call is:
;     build_sig(sig_stuff, rp, sig)

_build_sig:
	ret			; return to caller


;===========================================================================
;				get_chrome
;===========================================================================
; This routine calls the BIOS to find out if the display is monochrome or
; color.  The drivers are different, as	are the	video ram addresses, so	we
; need to know.

_get_chrome:
    ; color	= 1
	ret			; color	return
    ; mono = 0
	ret			; monochrome return


