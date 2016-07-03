/*
* print:  Print's an arbitrary file in a reasonable way
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Definitions

#define MAXCOLPOS 80
#define MAXWORD   13 // Based upon max hex plus format characters

/*
 * nextline(): move to the next line if the number of new characters added to the current
 *             position exceeds max
 */

static int nextline(int num, int pos, int max) {

	int newpos = pos + num;

	if (newpos > max) {
		(void)putchar('\n');
		return num;
	}

	return newpos;
}

/*
 * Main
 */

//int main(int argc, char *argv[]) {
int main(void) {

	int  pos = 1; // Column position of output
	int  len;     // Length of formatted output character string
	char c;       // Temp character buffer
	char s[MAXWORD];      // Formatted output character string
	int max = 0;

	while ((c = getchar()) != EOF) {

		// Pass all printable characters, tab, and line feed through without modification
		if (isprint(c) || c == '\n' || c == '\t')
			len = snprintf(s, MAXWORD, "%c", c);
		// Ignore carriage returns
		else if (c == '\r')
			len = snprintf(s, MAXWORD, "");
		// Print un-printable characters as a hex escape sequence
		else
			len = snprintf(s, MAXWORD, " \\x%x ", (unsigned)c);

		max = (len > max) ? len : max;
		pos = nextline(len, pos, MAXCOLPOS);
		printf("%s", s);

	}

	printf("max %d\n", max);

	exit(EXIT_SUCCESS);
}