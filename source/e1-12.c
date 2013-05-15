#include <stdio.h>

#define IN  1  /* inside a word */
#define OUT 0  /* outside a word */

/* count lines, words, and characters in the input */

main() {

	int c, bl;

	bl = 0;
	while ((c = getchar()) != EOF) {
		if (((c >= 'a') && (c <= 'z')) || 
              ((c >= 'A') && (c <= 'Z'))) {
			putchar(c);
			bl = 0;
		} else if ((c == ' ') || (c == '\n')) {
			if (bl == 0)
				putchar('\n');
			++bl;
		}
	}
}
