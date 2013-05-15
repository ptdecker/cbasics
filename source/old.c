#include <stdio.h>

#define MAXLEN   10  /* maximum word length to track */
#define MAXBAR   15  /* maximum bar size */
#define NONWORD   0  /* non-word state (not "in a word") */
#define COUNTLTR  1  /* count a word state (increment letter count) */
#define COUNTWRD  2  /* count word size state (incremenet word size) */
#define CONTRACT  3  /* in a contraction */

/* count lines, words, and characters in the input */

main() {

	int c, over, nc, i, j, state, max, scale;
	int nlen[MAXLEN];

	for (i = 0; i < MAXLEN; ++i)
		nlen[i] = 0;

	nc = over = 0;
	state = NONWORD;
	while ((c = getchar()) != EOF) {
		if (state == NONWORD && c >= 'a' && c <= 'z') {
			state = COUNTLTR;
			++nc;
		} else if (state == COUNTLTR && (c < 'a' || c > 'z')) {
			state = COUNTWRD;
			if (nc <= MAXLEN)
				++nlen[(nc-1)];
			else
				++over;
			nc = 0;
		} else if (state == COUNTLTR && c >= 'a' && c <= 'z') {
			state = COUNTLTR;
			++nc;
		} else if (state == COUNTLTR && c == '\'') {
			state = CONTRACT;
		} else if (state == COUNTWRD && c >= 'a' && c <= 'z') {
			state = COUNTLTR;
			++nc;
		} else if (state == COUNTWRD && (c < 'a' || c > 'z')) {
			state = NONWORD;
		} else if (state == CONTRACT && c >= 'a' && c <= 'z') {
			state = COUNTLTR;
		} else if (state == CONTRACT && (c < 'a' || c > 'z')) {
			state = COUNTWRD;
		}
	}

	max = 0;
	for (i = 0; i < MAXLEN; ++i)
		if (nlen[i] > max)
			max = nlen[i];
	if (over > max)
		max = over;

	scale = 1;
	if (max > MAXBAR) {
		scale = max / MAXBAR;
		if (max / scale > MAXBAR)
			++scale;
	}


	for (i = MAXBAR; i > 0; --i) {
		for (j = 0; j < MAXLEN; ++j) {
			if (i < (nlen[j] / scale))
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}


	for (i = 1; i <= MAXLEN; ++i)
		printf("%d", (i / 10) % 10);
	printf("%d", (MAXLEN / 10) % 10);
	printf("\n");

	for (i = 1; i <= MAXLEN; ++i)
		printf("%d", i % 10);
	printf("%d\n", MAXLEN % 10);

	for (i = 1; i <= MAXLEN; ++i)
		printf(" ");
	printf("+\n");

	printf("\n'*' = %d words\n", scale);

}
