// z88dk\include\_DEVELOPMENT\proto\stdarg.h

#ifndef __STDARG_H__
#define __STDARG_H__

#if defined(__CLANG)

typedef unsigned char * va_list;

#define va_start(marker, last)  { marker = (va_list)&last + sizeof(last); }
#define va_arg(marker, type)    *((type *)((marker += sizeof(type)) - sizeof(type)))
#define va_copy(dest, src)      { dest = src; }
#define va_end(marker)          { marker = (va_list) 0; };

#elif defined(__SDCC) || defined(__Z88DK_R2L_CALLING_CONVENTION)

// SDCC (or sccz80 with r2l mode)
// r->l parameter passing means there are no issues

/*-------------------------------------------------------------------------
   stdarg.h - ANSI macros for variable parameter list

   Copyright (C) 2000, Michael Hope
   Copyright (C) 2011, Philipp Klaus Krause pkk@spth.de

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License 
   along with this library; see the file COPYING. If not, write to the
   Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.

   As a special exception, if you link this library with other files,
   some of which are compiled with SDCC, to produce an executable,
   this library does not by itself cause the resulting executable to
   be covered by the GNU General Public License. This exception does
   not however invalidate any other reasons why the executable file
   might be covered by the GNU General Public License.
-------------------------------------------------------------------------*/

typedef unsigned char * va_list;

#define va_start(marker, last)  { marker = (va_list)&last + sizeof(last); }
#define va_arg(marker, type)    *((type *)((marker += sizeof(type)) - sizeof(type)))
#define va_copy(dest, src)      { dest = src; }
#define va_end(marker)          { marker = (va_list) 0; };

#define va_ptr(marker, type)    *((type *)(marker - sizeof(type)))

#elif defined(__SCCZ80)
#warning stdarg.h has many caveats when used in left-to-right mode.

// SCCZ80
// l->r parameter passing means compiler must tell us how many params are on the stack

// djm 28/2/2000

extern int __LIB__ getarg(void);

#define va_list                 unsigned char *
#define va_start(ap,last)       ap=(getarg()*2)+&last-7
#define va_arg(ap,type)         (*(type*)(ap-=sizeof(type),ap+1))
#define va_copy(dst, src)       dst = src
#define va_end(ap)

#define va_ptr(ap,type)         (*(type*)(ap+1))

#endif

#endif
