#include	<stdio.h>

#define	MAXLINE	1000		/* Maximum input line size */

/* Function prototypes */

int getln(char line[], int ml);

void copy(char to[], char from[]);

/* Print longest input line */

main () {

	int	len = 0;			/* Current line's length length */
	int	max = 0;			/* Maximum line length seen so far */
	char	line[MAXLINE];		/* Current input line */
	char longest[MAXLINE];	/* Longest line is saved so far */

	/* Find the longest line */

	max = 0;
	while ((len = getln(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}

	/* Print the longest line */

	if (max > 0)
		printf("%s", longest);
	else
		printf("No lines in input");

	return 0;

}

/* getln: read a line into s and return its length */

int getln(char s[], int lim) {

	int c, i;

	for (i=0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;

}

/* copy: copy 'from' into 'to' (assumes 'to' is big enough) */

void copy(char to[], char from[]) {

	int i;

	i = 0;

	while ((to[i] = from[i]) != '\0')
		++i;

}

