#include <stdio.h>

main() {

	int i, c;

	for (i = 32; i < 127; ++i) {
		c = i;

		/* convert uppercase to lowercase */

		if ('A' <= c && c <= 'Z')
			c = c - 'A' + 'a';


		putchar(c);
		if (i % 16 == 0)
			putchar('\n');
	}

}
