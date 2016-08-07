/*
* Convert case
*
* Converts to upper or lower depending upon how the program is called
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Definitions

#define NOT_FOUND -1;

/*
 * strindex(): Returns index of leftmost 't' inside 's' or -1 if not found
 */

static int strindex(char s[], char t[]) {

	size_t i;
	size_t j;
	size_t k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			; // Empty
		if (k > 0 && t[k] == '\0')
			return (int)i;
	}

	return NOT_FOUND;
}

/*
 * Main
 */


int main(/*@unused@*/int argc, char *argv[]) {

	int c;

	// Based upon the name of the program form argv[0] set pointer 'func' to the proper
	// transformation function ('lower' or 'upper')
	int (*func)(int) = (strindex(argv[0], "upper") < 0) ? tolower : toupper;

	while ((c = getchar()) != EOF)
		(void)putchar(func(c));

	return 0;
}