// NOTE: For information on OS X (OS X 10.11.6) versions of <fcntl.h> and <unistd.h> see:
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/unistd.h
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/fcntl.h

// NOTE: For inforation on OSMalloc see:
//           - https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/KernelProgramming/vm/vm.html#//apple_ref/doc/uid/TP30000905-CH210-CHDHIIJF

/*@ -incondefs -type -macrostmt -macrounrecog -mutrep -redef -retvalother -retvalint -exportlocal -globuse */


//# define NULL 0      // Not required--defiend in unistd.h
#define EOF      (-1)  // End-of-file indicator
#define BUFSIZ   1024  // Buffer size
#define OPEN_MAX 20    // Maximum number of files open at once

typedef struct _iobuf {
	int   cnt;            // Characters remaining in buffer
	char *ptr;            // Position of next character in buffer
	char *base;           // Buffer location
	int   flag;           // Mode of file access
	int   fd;             // File descriptor
} FILE;

FILE _iob[OPEN_MAX];

#define stdin  (&_iob[STDIN_FILENO])
#define stdout (&_iob[STDOUT_FILENO])
#define stderr (&_iob[STDERR_FILENO])

enum _flags {
	_READ  = 001,  // File open for reading flag bit
	_WRITE = 002,  // File open for writing flag bit
	_UNBUF = 004,  // Unbuffered file flag bit
	_EOF   = 010,  // End-of-file condition indicator flag bit
	_ERR   = 020   // Error condition indicator flag bit
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

/*@notfunction@*/
#define feof(p)    (((p)->flag & _EOF) != 0)

/*@notfunction@*/
#define ferror(p)  (((p)->flag & _ERR) != 0)

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
