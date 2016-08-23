// NOTE: For information on OS X (OS X 10.11.6) versions of <fcntl.h> and <unistd.h> see:
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/unistd.h
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/fcntl.h

// NOTE: For inforation on OSMalloc see:
//           - https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/KernelProgramming/vm/vm.html#//apple_ref/doc/uid/TP30000905-CH210-CHDHIIJF

#pragma clang diagnostic ignored "-Wdeprecated-declarations"	

#include <fcntl.h>
#include <stdlib.h> // form malloc, free
#include <unistd.h> // equivalent to (K&R) #include "syscalls.h"

#include "minstdio1.h"

#define PERMS 0666  // Read-write permissions for owner, group, others

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) NULL, (char *) NULL, _READ,           STDIN_FILENO},
	{ 0, (char *) NULL, (char *) NULL, _WRITE,          STDOUT_FILENO},
	{ 0, (char *) NULL, (char *) NULL, _WRITE | _UNBUF, STDERR_FILENO }
};

/*
 * fopen(): open a file and return a file pointer
 */

FILE *fopen(char *name, char *mode) {

	int   fd;  // File descriptor
	FILE *fp;

	// Only modes 'r' (read), 'w' (write), and 'a' (append) are supported
	// so bail out if we're asked to do something else
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	// Find a free slot in the file pointer array and, if we do not
	// find one, then bail out
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;

	// Create the file (if needed) and open it using the requested mode
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);

	// Bail out if we couldn't access name
	if (fd == -1)
		return NULL;

	// Populate the file pointer
	fp->cnt  = 0;        // Initially, no characters are buffered and...
	fp->base = NULL;     // a buffer to hold such has not been initialized
	fp->ptr  = NULL;     // so we certainly cannot be pointing at any contents
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	fp->fd   = fd;

	return fp;
}

/*
 * _fillbuf(): Allocate and fill an input buffer
 */

int _fillbuf(FILE *fp) {

	int bufsize = 0; // Size of buffer allocation

	// Make sure we are in read mode and neither EOF nor ERR indicators have been set.
	// If not the case, then politely return EOF condition
	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;

	// Calculate buffer size and attempt to allocate it.  If unable to allocate,
	// return EOF condition
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;

	// Fill the buffer as much as we can
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	// Handle if either an end of file or error condition occurred
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char) *fp->ptr++;
}

/*
 * _flushbuf(): Flush an output buffer
 */

int _flushbuf(int x, FILE *fp) {

	unsigned nc; // Number of characters to flush
	int bufsize; // Size of buffer allocation

	// Confirm we were passed a valid file pointer, that the ERR indicator is not set,
	// and that we are in write mode.  If not the case, politely return EOF condition
	if (fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;
	if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
		return EOF;

	// Set buffer size
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	// Check to see if a buffer has been allocated and act accordingly
	if (fp->base == NULL) {

		// No buffer has been allocated yet, so attempt to allocate one. If we
		// cannot, set ERR indicator and return EOF condition; otherwise
		if ((fp->base = (char *)malloc(bufsize)) == NULL) {
			fp->flag |= _ERR;
			return EOF;
		}

	} else {

		// A buffer has been allocated so go aehad and write it out and
		// deal with any consequences
		nc = fp->ptr - fp->base;
		if (write(fp->fd, fp->base, nc) != nc) {
			fp->flag |= _ERR;
			return EOF;
		}
		
	}

	// Maintain the file pointer and save the character
	fp->ptr = fp->base;
	fp->cnt = bufsize - 1;
	*fp->ptr++ = (char) x;

	return x;
}

/*
 * fflush(): flush a buffer associated with a file pointer
 */

int fflush(FILE *fp) {

	int rc = 0;

	// Make sure we are being asked to flush a valid file pointer
	if (fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;

	if (fp->flag & _WRITE)
		rc = _flushbuf(0, fp);

	fp->ptr = fp->base;
	fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	return rc;
}

/*
 * fseek(): seek within a file pointer
 */

int fseek(FILE *fp, long offset, int origin) {

	unsigned nc;  // Number of characters to flush
	long rc = 0;  // Return code

	// Take action based upon the current access mode (read or write) 
	// of the file
	if (fp->flag & _READ) {

		// We're in a read access mode
		// If origin is set to '1' we are reading from the current position
		// but need to take the characters in the buffer into account, seek to 
		// our adjusted position, and discard any buffered characters.  Note: if
		// origin is set to '0' (beginning of file) or '2' (end of file) then
		// the current buffer contents do not need to be accounted for.
		if (origin == 1)
			offset -= fp->cnt;
		rc = lseek(fp->fd, offset, origin);
		fp->cnt = 0;

	} else if (fp->flag & _WRITE) {

		// We're in a write access mode (includes append) so all nwee need to do is 
		// write out any buffered characters then, if successful, seek to our new
		// position.  Origin does not matter in any case.
		nc = (fp->ptr - fp->base);
		if (nc > 0)
			if (write(fp->fd, fp->base, nc) != nc)
				rc = -1;
		if (rc != -1)
			rc = lseek(fp->fd, offset, origin);

	}

	// return appropriate return code
	return (rc == -1) ? -1 : 0;
}

/*
 * fclose(): close a file
 */

int fclose(FILE *fp) {

	int rc;

	if ((rc = fflush(fp)) != EOF) {
		free(fp->base);
		fp->ptr = NULL;
		fp->cnt = 0;
		fp->base = NULL;
		fp->flag &= ~(_READ | _WRITE);
	}

	return rc;
}

/*
 * puts(): write out a string to file using putc();
 */

void puts(char *str, FILE *fp) {
	while (*str != '\0')
		putc(*str++, fp);
}

/*
 * putstring(): write out a string to standard out using putchar()
 */

void putstring(char *str) {
	while (*str != '\0')
		putchar(*str++);
}

