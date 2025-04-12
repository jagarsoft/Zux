CC=zcc
AS=zcc
#TARGET=+z80
TARGET=+Zux
VERBOSITY=-v
# -no-cleanup --c-code-in-asm -fverbose-asm -z80-verb -gen-map-file -gen-symbol-file --list 
#DEFINES=-DZ80
#CRT=-crt0=../lib/crt_mmfs.asm.m4
#Z88DKFLAGS=-O3 -Wimplicit-function-definition -nostdlib -clib=new -startup=0 -pragma-include=ZuxPragma.inc
#INCFLAGS=-I"." -I"../include" -I"../h"
#LIBFLAGS=-L"../lib"
CFLAGS=$(TARGET) $(VERBOSITY) $(DEFINES) $(Z88DKFLAGS) $(INCFLAGS) $(LIBFLAGS) -startup=2
h=../h
#l=-lZuxlib.lib

obj =	main.o forkexit.o break.o exec.o signal.o getset.o alloc.o utility.o table.o putc.o

OUT = mm.bin

all: $(OUT)

#mm:	makefile  $l/head.o $(obj) $l/libc.a $l/end.o
$(OUT):	makefile  $(obj) ../kernel/kernel_org.inc mm_org.inc
	@echo "Start linking MM"
#	@ld -o mm $l/head.o $(obj) $l/libc.a $l/end.o
	@$(CC) $(CFLAGS) -o $(OUT) $(obj)
ifeq ($(CMDSHELL),CMD)
	<nul set /p ="MM org " > org.tmp
	type ..\kernel\kernel_len.txt >> org.tmp
	type org.tmp
	del org.tmp
	for /f %A in (..\kernel\kernel_len.txt) do z88dk-dis -o %A -x fs.map $(OUT) > $(OUT).asm
	..\tools\wcut.cmd $(OUT) > mm_len.txt
	<nul set /p ="defc FS_ORG = " > fs_org.tmp
	set /p KERNEL_LEN=<../kernel/kernel_len.txt
	set /p MM_LEN=<mm_len.txt
	set /a TOTAL=%KERNEL_LEN%+%MM_LEN%
	echo %TOTAL% >> fs_org.tmp
	move /Y fs_org.tmp ..\fs\fs_org.inc
	<nul set /p ="MM done: " > done.tmp
	type mm_len.txt >> done.tmp
	<nul set /p =" bytes" >> done.tmp
	type done.tmp
	del done.tmp
else
# CMDSHELL=BASH
	echo MM org `cat ../kernel/kernel_len.txt`
	z88dk-dis -o `cat ../kernel/kernel_len.txt` -x fs.map $(OUT) > $(OUT).asm
	ls -l $(OUT) | cut -d' ' -f 5 > mm_len.txt
	awk 'BEGIN { print '`cat ../kernel/kernel_len.txt`' + '`cat mm_len.txt`' }' > ker_mm_len.txt
	echo "defc FS_ORG = `cat ker_mm_len.txt`" > ../fs/fs_org.inc
	echo "MM done: `cat mm_len.txt` bytes"
endif

../kernel/kernel_org.inc:

mm_org.inc:

alloc.o:	const.h $h/const.h $h/type.h

break.o:	const.h $h/const.h $h/type.h
break.o:	$h/error.h
break.o:	$h/signal.h
break.o:	glo.h
break.o:	mproc.h
break.o:	param.h

exec.o:		const.h $h/const.h $h/type.h
exec.o:		$h/callnr.h
exec.o:		$h/error.h
exec.o:		$h/stat.h
exec.o:		glo.h
exec.o:		mproc.h
exec.o:		param.h

forkexit.o:	const.h $h/const.h $h/type.h
forkexit.o:	$h/callnr.h
forkexit.o:	$h/error.h
forkexit.o:	glo.h
forkexit.o:	mproc.h
forkexit.o:	param.h

getset.o:	const.h $h/const.h $h/type.h
getset.o:	$h/callnr.h
getset.o:	$h/error.h
getset.o:	glo.h
getset.o:	mproc.h
getset.o:	param.h

main.o:		const.h $h/const.h $h/type.h
main.o:		$h/callnr.h
main.o:		$h/com.h
main.o:		$h/error.h
main.o:		glo.h
main.o:		mproc.h
main.o:		param.h

putc.o:		$h/const.h $h/type.h
putc.o:		$h/com.h

signal.o:	const.h $h/const.h $h/type.h
signal.o:	$h/callnr.h
signal.o:	$h/com.h
signal.o:	$h/error.h
signal.o:	$h/signal.h
signal.o:	$h/stat.h
signal.o:	glo.h
signal.o:	mproc.h
signal.o:	param.h

table.o:	const.h $h/const.h $h/type.h
table.o:	$h/callnr.h
table.o:	glo.h
table.o:	mproc.h
table.o:	param.h

utility.o:	const.h $h/const.h $h/type.h
utility.o:	$h/callnr.h
utility.o:	$h/com.h
utility.o:	$h/error.h
utility.o:	$h/stat.h
utility.o:	glo.h
utility.o:	mproc.h

clean:
ifeq ($(CMDSHELL),CMD)
	if exist $(OUT) del $(OUT)
	del *.o *.lis *sym *.lst *.map $(OUT)
else
	rm -f *.o *.lis *sym *.lst *.map $(OUT)
endif

clean-inc:
ifeq ($(CMDSHELL),CMD)
	if exist mm_org.inc del mm_org.inc
	if exist fs_org.inc del fs_org.inc
else
	rm -f mm_org.inc fs_org.inc
endif