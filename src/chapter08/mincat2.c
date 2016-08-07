/*
* mincat: minimal version of 'cat' which concatinates files using stdio functions
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // used to time process

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
 * filecopy(): copy file ifp to file ofp
 */

static void filecopy(FILE *ifp, FILE *ofp) {

	int c;

	while ((c = getc(ifp)) != EOF)
		(void)putc(c, ofp);
}

/*
 * main
 */

int main(int argc, char *argv[]) {

	FILE   *fp;
	char   *prog = argv[0];  // Program name for errors
	clock_t start = clock();

	if (argc == 1) {
		filecopy(stdin, stdout);
		return 0;
	}

	while (--argc > 0)
		if ((fp = fopen(*++argv, "r")) == NULL)
			error("%s: cannot open %s\n", prog, *argv);
		else {
			filecopy(fp, stdout);
			(void)fclose(fp);
		}

	if (ferror(stdout) != 0)
		error("%s: error writing stdout\n", prog);

	printf("Run time: %u clock ticks\n", (unsigned)(clock() - start));
	exit(EXIT_SUCCESS);
}