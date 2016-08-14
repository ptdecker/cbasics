/*@ -mutrep  -incondefs -type -macrounrecog */

#define BUFSIZ    1024   // size of buffer
#define EOF       (-1)   // end-of-file sentinel value
#define NULL         0   // NULL sentinel value
#define OPEN_MAX    20   // maximum number of open files
#define EXIT_SUCCESS 0   // Include EXIT_SUCCESS so <stdlib.h> isn't needed
#define EXIT_FAILURE 1   // Include EXIT_FAILURE so <stdlib.h> isn't needed

typedef struct _iobuf {
	int   cnt;  // characters remaining in buffer
	char *ptr;  // next character position
	char *base; // location of buffer
	int   flag; // mode of file access
	int   fd;   // file descriptor
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
	_READ  =  01, // file open for reading
	_WRITE =  02, // file open for writing
	_UNBUF =  04, // file is unbuffered
	_EOF   = 010, // EOF has occurred on this file
	_ERR   = 020  // An error has occured on this file
};

int _fillbuff(FILE *);
int _flushbuff(int, FILE *);

#define feof(p)   (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p)   (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuff(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x)           : _flushbuff((x),p))

#define getchar()  getc(stdin)
#define putchar(x) putc((x),stdout)

FILE *fopen(char *name, char *mode);
void fprint(FILE *, char *);
