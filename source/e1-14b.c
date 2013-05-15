#include <stdio.h>

#define MAXLTRS  26  /* number of letters */
#define MAXBAR   18  /* maximum bar size */

/* vertical histogram of character frequencies */

main() {

	int c, i, j, max, scale;
	int nltrs[MAXLTRS];

	/* initialize letter count array */

	for (i = 0; i < MAXLTRS; ++i)
		nltrs[i] = 0;

	/* count letter frequencies (case insensitive) */

	while ((c = getchar()) != EOF)
		if ('a' <= c && c <= 'z')
			++nltrs[c-'a'];
		else if ('A' <= c && c <= 'Z')
			++nltrs[c-'A'];

	/* find maximum letter count */

	max = 0;
	for (i = 0; i < MAXLTRS; ++i)
		if (nltrs[i] > max)
			max = nltrs[i];

	/* determine scale */

	scale = 1;
	if (max > MAXBAR) {
		scale = (max / MAXBAR);
		if (max / scale > MAXBAR)
			++scale;
	}

	/* print vertical histogram */

	for (i = (max / scale) - 1; i >= 0; --i) {
		for (j = 0; j < MAXLTRS; ++j) {
			if (i < (nltrs[j] / scale))
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}

	/* print axis labels */


	for (i = 0; i < MAXLTRS; ++i)
		printf("%c", (i + 'A'));
	printf("\n");

	/* print scale */

	printf("\n'*' = %d letter", scale);
	if (scale > 1)
		printf("s");
	printf("\n");

}
