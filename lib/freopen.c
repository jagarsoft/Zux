#include "../include/stdio.h"

FILE *freopen(name,mode,stream)
char *name,*mode;
FILE *stream;
{
	extern FILE *fopen();

	if ( fclose(stream) != 0 )
		return NULL;

	return fopen(name,mode);
}
