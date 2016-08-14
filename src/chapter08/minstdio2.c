/*
* minstdio.o - Minimal implemenation of stdio file functions
*/

/*@  -type  -globstate -fcnuse */

// NOTE: For information on OS X (OS X 10.11.6) versions of <fcntl.h> and <unistd.h> see:
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/unistd.h
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/fcntl.h

#include <fcntl.h>
#include "minstdio.h"  // using our own custom min <stdio.h>
#include <stdlib.h>
#include <time.h>      // used to time process
#include <unistd.h>    // equivalent to (K&R) #include "syscalls.h"

// Constant definitions

#define PERMS    0666 // 'read' and 'write' for 'owner', 'group', and 'others'

// Globals

static FILE _iob[OPEN_MAX] = {
	{ 0, NULL, NULL, _READ,           0}, // stdin
	{ 0, NULL, NULL, _WRITE,          1}, // stdout
	{ 0, NULL, NULL, _WRITE | _UNBUF, 2}  // stderr (unbuffered)
};

/*
 * fopen(): open a file returning a pointer
 */

FILE *fopen(char *name, char *mode) {

	int   fd; // file descriptor number
	FILE *fp; // file pointer

	// This version of fopen only supports 'read', 'write', and 'append' modes so
	// make sure we're being asked to use one of them instead of something else
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	// Look through the file descriptor blocks for an open slot.  If we make
	// it to the end without finding one, then return NULL
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;

	// Depending upon our mode, set up our access to the file using low-level
	// operating system functions
	if (*mode == 'w')
		// 'write' mode
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		// 'append' mode
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		(void)lseek(fd, 0L, 2);
	} else
		// 'read' mode
		fd = open(name, O_RDONLY, 0);

	// If we failed to get things set up, bail out
	if (fd == -1)
		return NULL;

	// Update the file pointer record
	fp->fd   = fd;
	fp->cnt  = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;

	// Return it
	return fp;
}

/*
 * _fillbuf(): allocate and fill the input buffer
 */

int _fillbuff(FILE *fp) {

	size_t bufsize;

	// Verify we are in 'read' mode and that no errors nor end-of-file
	// condition has been set
	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;

	// Determine the size of the buffer
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	// Allocate the buffer if needed and read into it if possible
	if (fp->base == NULL)
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	// Check for either an end-of-file or an error condition
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}

	// Return pointer to buffer
	return (unsigned char)*fp->ptr++;
}

/*
 * fprint(): a basic function to output a string to a file
 */

void fprint(FILE *file, char *msg) {
	while (*msg != '\0')
		putc(*msg, file);
}
