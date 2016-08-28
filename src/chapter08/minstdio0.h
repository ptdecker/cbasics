/*
 * Header for a minimal implementation of the 'stdio' standard C library
 *
 * NOTE:  This version 'minstdio0.h' is implemented using bit fields as opposed to bit manipulaiton
 *        operations.  Contrast with 'minstdio.h'
 */

// NOTE: For information on OS X (OS X 10.11.6) versions of <fcntl.h> and <unistd.h> see:
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/unistd.h
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/fcntl.h

// NOTE: For inforation on OSMalloc see:
//           - https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/KernelProgramming/vm/vm.html#//apple_ref/doc/uid/TP30000905-CH210-CHDHIIJF

/*@ -incondefs -type -mutrep */

// Includes

#include <fcntl.h>
#include <stdlib.h> // form malloc, free
#include <unistd.h> // equivalent to (K&R) #include "syscalls.h"

// Definitions

#define EOF      (-1)  // End-of-file indicator
#define BUFSIZ   1024  // Buffer size
#define OPEN_MAX 20    // Maximum number of files open at once

typedef struct _iobuf {
	int   cnt;            // Characters remaining in buffer
	char *ptr;            // Position of next character in buffer
	char *base;           // Buffer location
	struct _flags {
		unsigned int is_read  : 1;
		unsigned int is_write : 1;
		unsigned int is_unbuf : 1;
		unsigned int is_buf   : 1;
		unsigned int is_eof   : 1;
		unsigned int is_err   : 1;
	} flags;
	int   fd;             // File descriptor
} FILE;

FILE _iob[OPEN_MAX];

#define stdin  (&_iob[STDIN_FILENO])
#define stdout (&_iob[STDOUT_FILENO])
#define stderr (&_iob[STDERR_FILENO])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

/*@notfunction@*/
#define feof(p)    ((p)->flag.is_eof)

/*@notfunction@*/
#define ferror(p)  ((p)->flag.is_err)

/*@notfunction@*/
#define fileno(p)  ((p)->fd)

/*@notfunction@*/
#define getc(p)    ((--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p)))

/*@notfunction@*/
#define putc(x,p)  ((--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p)))

/*@notfunction@*/
#define getchar()  getc(stdin)

/*@notfunction@*/
#define putchar(x) putc((x), stdout)

int fflush(FILE *fp);
FILE *fopen(char *name, char *mode);
int fclose(FILE *fp);
void puts(char *str, FILE *fp);
void putstring(char *str);
