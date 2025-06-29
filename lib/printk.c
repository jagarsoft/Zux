/* This is a special version of printf.  It is used only by the operating
 * system itself, and should never be included in user programs.   The name
 * printk never appears in the operating system, because the macro printf
 * has been defined as printk there.
 */

#include "stdarg.h"

#define MAXDIGITS         12

#ifdef Z80
void putsk(unsigned char *s);
void __FASTCALL__ putck(unsigned char c);
#define putc putck
#else
extern void putc(char c);
#endif

void printk(const char *fmt,...);
static void _printk(char *s, int *arglist);
int bintoascii(long num, int radix, char a[MAXDIGITS]);

void printk(const char *fmt,...)
{
  va_list ap;
  va_start(ap,fmt);
  _printk(fmt, ap);
  va_end(ap);
}

static void _printk(s, arglist)
char *s;
int *arglist;
{
  int w, k, r, *valp;
  unsigned u;
  long l, *lp;
  char a[MAXDIGITS], *p, *p1, c;

  while (*s != '\0') {
	if (*s !=  '%') {
		putc(*s++);
		continue;
	}

	valp = (int *)  &arglist;
	w = 0;
	s++;
	while (*s >= '0' && *s <= '9') {
		w = 10 * w + (*s - '0');
		s++;
	}

	lp = (long *) valp;

	switch(*s) {
	    case 'd':	k = *valp++; l = k;  r = 10;  break;
	    case 'o':	k = *valp++; u = k; l = u;  r = 8;  break;
	    case 'x':	k = *valp++; u = k; l = u;  r = 16;  break;
	    case 'D':	l = *lp++;  r = 10; valp = (int *) lp; break;
	    case 'O':	l = *lp++;  r = 8;  valp = (int *) lp; break;
	    case 'X':	l = *lp++;  r = 16; valp = (int *) lp; break;
	    case 'c':	k = *valp++; putc(k); s++; continue;
	    case 's':	p = (char *) *valp++; 
			p1 = p;
			while(c = *p++) putc(c); s++;
			if ( (k = w - (p-p1-1)) > 0) while (k--) putc(' ');
			continue;
	    default:	putc('%'); putc(*s++); continue;
	}

	k = bintoascii(l, r, a);
	if ( (r = w - k) > 0) while(r--) putc(' ');
	for (r = k - 1; r >= 0; r--) putc(a[r]);
	s++;
  }
}



int bintoascii(num, radix, a)
long num;
int radix;
char a[MAXDIGITS];
{

  int i, n, hit, negative;

  negative = 0;
  if (num == 0) {a[0] = '0'; return(1);}
  if (num < 0 && radix == 10) {num = -num; negative++;}
  for (n = 0; n < MAXDIGITS; n++) a[n] = 0;
  n = 0;

  do {
	if (radix == 10) {a[n] = num % 10; num = (num -a[n])/10;}
	if (radix ==  8) {a[n] = num & 0x7;  num = (num >> 3) & 0x1FFFFFFF;}
	if (radix == 16) {a[n] = num & 0xF;  num = (num >> 4) & 0x0FFFFFFF;}
	n++;
  } while (num != 0);

  /* Convert to ASCII. */
  hit = 0;
  for (i = n - 1; i >= 0; i--) {
	if (a[i] == 0 && hit == 0) {
		a[i] = ' ';
	} else {
		if (a[i] < 10)
			a[i] += '0';
		else
			a[i] += 'A' - 10;
		hit++;
	}
  }
  if (negative) a[n++] = '-';
  return(n);
}

#ifdef Z80
void putsk(unsigned char *s) {
	while (*s != '\0') {
          putck(*s++);
	}
}

void __FASTCALL__ putck(unsigned char c)
{
  // https://www.z88dk.org/forum/viewtopic.php?p=22863&sid=95e6655ce9bac030f0007ae5cbcafc4e#p22863

  __asm
      	ld	a, l
		rst	0x10
IF STANDARDESCAPECHARS
		cp 0x0a
		jr	nz, putsk_L0
		ld	a, 0x0d
ELSE
      	cp 0x0d
		jr	nz, putsk_L0
		ld	a, 0x0a
ENDIF
        rst	0x10
.putsk_L0:
   __endasm;
}

#endif