CC=zcc
AS=zcc
#TARGET=+z80
TARGET=+Zux
VERBOSITY=-v
#DEFINES=-DZ80
#CRT=-crt0 ../lib/crt_mmfs.asm
#Z88DKFLAGS=-O3 -Wimplicit-function-definition -nostdlib -clib=new -startup=0 -no-cleanup
#INCFLAGS=-I"." -I"../include" -I"../h"
#LIBFLAGS=-L"../lib"
CFLAGS=$(TARGET) $(VERBOSITY) $(DEFINES) $(Z88DKFLAGS) $(INCFLAGS) $(LIBFLAGS) -startup=3
#l=-lZuxlib.lib

SRC = cache.c device.c filedes.c inode.c link.c main.c misc.c mount.c open.c path.c pipe.c protect.c putc.c read.c stadir.c super.c table.c time.c utility.c write.c data_org.asm
OBJ = cache.o device.o filedes.o inode.o link.o main.o misc.o mount.o open.o path.o pipe.o protect.o putc.o read.o stadir.o super.o table.o time.o utility.o write.o data_org.o
OUT = fs.bin

all: $(OUT)

fs.bin: makefile $(OBJ) ../kernel/kernel_org.inc ../mm/mm_org.inc fs_org.inc
	@echo "Start linking FS"
	@$(CC) $(CFLAGS) -o $(OUT) $(OBJ)
ifeq ($(CMDSHELL),CMD)
	<nul set /p ="FS org " > org.tmp
	type ../mm/ker_mm_len.txt >> org.tmp
	type org.tmp
	del org.tmp
	for /f %A in (../mm/ker_mm_len.txt) do z88dk-dis -o %A -x fs.map $(OUT) > $(OUT).asm
	tools\wcut.cmd $(OUT) > fs_len.txt
	<nul set /p ="defc INIT_ORG = " > init_org.tmp
	set /p KERNEL_MM_LEN=<../mm/ker_mm_len.txt
	set /p FS_LEN=<fs_len.txt
	set /a TOTAL=%KERNEL_MM_LEN%+%FS_LEN%
	echo %TOTAL% >> init_org.tmp
	move /Y init_org.tmp ..\tools\init_org.inc
	<nul set /p ="FS done: " > done.tmp
	type fs_len.txt >> done.tmp
	<nul set /p =" bytes" >> done.tmp
	type done.tmp
	del done.tmp
else
	echo FS org `cat ../mm/ker_mm_len.txt`
	z88dk-dis -o `cat ../mm/ker_mm_len.txt` -x fs.map $(OUT) > $(OUT).asm
	ls -l $(OUT) | cut -d' ' -f 5 > fs_len.txt
	awk 'BEGIN { print '`cat ../kernel/kernel_len.txt`' + '`cat ../mm/mm_len.txt`' + '`cat fs_len.txt`' }' > ker_mm_fs_len.txt
	echo "defc INIT_ORG = `cat ker_mm_fs_len.txt`" > ../tools/init_org.inc
	echo "FS done: `cat fs_len.txt` bytes"
endif

../kernel/kernel_org.inc:

../mm/mm_org.inc:

fs_org.inc:

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AS) $(CFLAGS) -c -o $@ $<

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
else
	rm -f mm_org.inc
endif