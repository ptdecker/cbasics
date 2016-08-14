/*
* mincat: minimal version of 'cat' which concatinates files using stdio functions
*/

#include "minstdio.h"

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

	if (argc == 1) {
		filecopy(stdin, stdout);
		return EXIT_SUCCESS;
	}

	while (--argc > 0)
		if ((fp = fopen(*++argv, "r")) == NULL) {
			fprint(stderr, "error: cannot open specified file\n");
			return EXIT_FAILURE;
		} else {
			filecopy(fp, stdout);
			(void)fclose(fp);
		}

	if (ferror(stdout) != 0) {
		fprint(stderr, "error: error writing stdout\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}