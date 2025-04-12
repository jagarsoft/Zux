# zcc +z80 -DZ80 -O3 -v -startup=0 -clib=new -c *.c
# z80asm -v -d -x$(OUT) @Zuxlib.lst

CC=zcc
AS=zcc
TARGET=+Zux
VERBOSITY=-v
CFLAGS=$(TARGET) $(VERBOSITY) 

SRC = abort.c abs.c access.c alarm.c atoi.c atol.c bcopy.c brk.c brk2.c call.c chdir.c chmod.c chown.c chroot.c cleanup.c close.c creat.c crypt.c ctype.c doprintf.c doscanf.c dup.c dup2.c exec.c exit.c fclose.c fflush.c fgets.c fopen.c fork.c fprintf.c fputs.c fread.c freopen.c fseek.c fstat.c ftell.c fwrite.c getc.c getegid.c getenv.c geteuid.c getgid.c getgrent.c getpass.c getpid.c getpwent.c gets.c getuid.c index.c ioctl.c isatty.c itoa.c kill.c link.c lseek.c malloc.c message.c mknod.c mktemp.c mount.c open.c pause.c perror.c pipe.c printdat.c printk.c prints.c putc.c rand.c read.c regexp.c regsub.c rindex.c scanf.c setbuf.c setgid.c setuid.c signal.c sleep.c sprintf.c stat.c stb.c stderr.c stime.c strcat.c strcmp.c strcpy.c strlen.c strncat.c strncmp.c strncpy.c sync.c syslib.c time.c times.c umask.c umount.c ungetc.c unlink.c utime.c wait.c write.c getutil.asm sendrec.asm
OBJ = abort.o abs.o access.o alarm.o atoi.o atol.o bcopy.o brk.o brk2.o call.o chdir.o chmod.o chown.o chroot.o cleanup.o close.o creat.o crypt.o ctype.o doprintf.o doscanf.o dup.o dup2.o exec.o exit.o fclose.o fflush.o fgets.o fopen.o fork.o fprintf.o fputs.o fread.o freopen.o fseek.o fstat.o ftell.o fwrite.o getc.o getegid.o getenv.o geteuid.o getgid.o getgrent.o getpass.o getpid.o getpwent.o gets.o getuid.o index.o ioctl.o isatty.o itoa.o kill.o link.o lseek.o malloc.o message.o mknod.o mktemp.o mount.o open.o pause.o perror.o pipe.o printdat.o printk.o prints.o putc.o rand.o read.o regexp.o regsub.o rindex.o scanf.o setbuf.o setgid.o setuid.o signal.o sleep.o sprintf.o stat.o stb.o stderr.o stime.o strcat.o strcmp.o strcpy.o strlen.o strncat.o strncmp.o strncpy.o sync.o syslib.o time.o times.o umask.o umount.o ungetc.o unlink.o utime.o wait.o write.o getutil.o sendrec.o
OUT = Zuxlib.lib

all: $(OUT)

$(OUT): $(OBJ)
ifeq ($(CMDSHELL),CMD)
# CMDSHELL=CMD
	if exist $(OUT) del $(OUT)
else
# CMDSHELL=BASH
	rm -f $(OUT)
endif
	z80asm -v -d -x$(OUT) *.o
	echo Created $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AS) $(CFLAGS) -c -o $@ $<

clean:
#	del *.o *.lis *sym *.lst *.map fs.bin
ifeq ($(CMDSHELL),CMD)
	if exist $(OUT) del $(OUT)
	del *.o *.lis *sym *.lst *.map
else
	rm -f *.o *.lis *sym *.lst *.map $(OUT)
endif