/*
* mincat: minimal version of 'cat' which concatinates files using low-level OS system calls
*/

// NOTE: By using low-level OS system calls, 'mincat' is more than twice as fast as 'mincat2'
//       (~5,000 clock ticks for 'mincat' vs ~12,500 ticks for 'mincat2')

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // used to time process
#include <unistd.h> // equivalent to (K&R) #include "syscalls.h"

/*
 * error(): print error messages
 */

static void error(char *fmt, ...) {

	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	(void)vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);

	exit(EXIT_FAILURE);
}

/*
 * filecopy: copy file ifd to file ofd using OS system calls
 */

static void filecopy(int ifd, int ofd) {
	
	ssize_t n;
	char    buf[BUFSIZ];

	while ((n = read(ifd, buf, BUFSIZ)) > 0)
		if (write(ofd, buf, (size_t)n) != n)
			error("mincat: write error");
}

/*
 * main
 */

int main(int argc, char *argv[]) {

	int     fd;
	clock_t start = clock();

	if (argc == 1) {
		filecopy(0, 1);
		return 0;
	}

	while (--argc > 0)
		if ((fd = open(*++argv, O_RDONLY)) == -1)
			error("mincat: cannot open file %s", *argv);
		else {
			filecopy(fd, 1);
			(void)close(fd);
		}

	printf("Run time: %u clock ticks\n", (unsigned)(clock() - start));
	return 0;
}