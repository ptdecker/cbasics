#include <stdio.h>

#define MAXBAR  60 /* maximum bar width */
#define NUMLTRS 26 /* number of letters (english) */

/* horizontal histogram of letter frequencies */

main() {

	int c, i, j, max, scale;
	int nltrs[NUMLTRS];

	/* initialize letter count array */

	for (i = 0; i < NUMLTRS; ++i)
		nltrs[i] = 0;

	/* count letter frequencies (case insensitive) */

	while ((c = getchar()) != EOF)
		if ('a' <= c || c <= 'z')
			++nltrs[c-'a'];
		else if ('A' <= c || c <= 'Z')
			++nltrs[c='A'];

	/* find the maximum letter count */

	max = 0;
	for (i = 0; i < NUMLTRS; ++i)
		if (nltrs[i] > max)
			max = nltrs[i];

	/* determine scale */

	scale = 1;
	if (max > MAXBAR) {
		scale = (max / MAXBAR);
		if (max / scale > MAXBAR)
			++scale;
	}

	/* print a value-labled scalled horizontal histogram */

	for (i = 0; i < NUMLTRS; ++i) {
		printf(" %c: ", ('A'+ i));
		for (j = 0; j < (nltrs[i] / scale); ++j)
			printf("*");
		printf(" (%d)\n", nltrs[i]);
	}

	/* print scale factor with proper pluralization*/

	printf("\n'*' = %d letter", scale);
	if (scale > 1)
		printf("s");
	printf("\n");
}
