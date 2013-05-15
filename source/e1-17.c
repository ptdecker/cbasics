#include <stdio.h>

#define MAXLINE 1000 /* Note: MAXLINE includes terminating newline and null characters */
#define BIGLINE 80   /* Defines the minimum size of a line that will be printed */

/* Functional prototypes */

int getbigline(char line[], int maxline);

/* Prints any line equal too or larger than BIGLINE in size (up to MAXLINE characters) */

main() {

	char	line[MAXLINE];
	int	len = 0;

	while ((len = getbigline(line, MAXLINE)) > 0)
		if (len > BIGLINE)
			printf("%s", line);
}

/* getbigline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

int getbigline(char s[], int lim) {

	int c, len, slen;

	len = slen = 0;
	while ((c = getchar()) != EOF && c != '\n') {
		if (slen < (lim - 2))
			s[slen++] = c;
		++len;
	}

	s[slen++] = '\n';
	s[slen] = '\0';

	return len;
	
}
