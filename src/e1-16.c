#include <stdio.h>

#define MAXLINE 1000 /* Note: MAXLINE includes terminating newline and null characters */

/* Functional prototypes */

int getbigline(char line[], int maxline);

void copy(char to[], char from[]);

/* Display the length of the longest arbitrarily long input line and as
 * much of that line as possible.
 */

main() {

	int c, nl, len, maxlen;
	char line[MAXLINE];
	char longest[MAXLINE];

	maxlen = len = nl = 0;

	while ((len = getbigline(line, MAXLINE)) > 0) {
		if (len > maxlen) {
			maxlen = len;
			copy(longest, line);
		}
		++nl;
	}

	printf("%d line%s read.\n", nl, (nl == 1)?"":"s");
	if (nl > 0) {
		printf("The longest line is %d character%s long.\n", maxlen, (maxlen == 1)?"":"s");
		if (maxlen > MAXLINE)
			printf("The first part of the longest line is: %s", longest);
		else
			printf("The longest line is: %s", longest);
	}


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

/* copy: copy 'from' into 'to'; assume to is big enough */

void copy(char to[], char from[]) {

	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;

}
