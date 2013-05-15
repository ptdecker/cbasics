#include <stdio.h>

#define MAXLEN   70  /* maximum word length to keep track of */
#define MAXBAR   16  /* maximum bar width */
#define NONWORD   0  /* "not in a word" state */
#define COUNTLTR  1  /* counting letters in a word state */
#define COUNTWRD  2  /* counting word lengths state */
#define CONTRACT  3  /* handling a contraction state */

/* print a horizontal histogram of word lengths */

main() {

	int c, over, nc, i, j, state, max, scale, width;
	int nlen[MAXLEN];

	/* initialize word length array */

	for (i = 0; i < MAXLEN; ++i)
		nlen[i] = 0;

	/* count word lengths using a finite state machine */

	nc = over = 0;
	state = NONWORD;
	while (1) {

		/* get character or EOF */

		c = getchar();

		/* convert uppercase characters to lowercase */

		if ('A' <= c && c <= 'Z')
			c = c - 'A' + 'a';

		/* handle state transitions */

		if (c == EOF)
			state = EOF;
		else if (state == NONWORD && 'a' <= c && c <= 'z')
			state = COUNTLTR;
		else if (state == NONWORD && (c < 'a' || 'z' < c))
			state = NONWORD;
		else if (state == COUNTLTR && 'a' <= c && c <= 'z')
			state = COUNTLTR;
		else if (state == COUNTWRD && 'a' <= c && c <= 'z')
			state = COUNTLTR;
		else if (state == CONTRACT && 'a' <= c && c <= 'z')
			state = COUNTLTR;
		else if (state == COUNTLTR && (c < 'a' || 'z' < c))
			state = COUNTWRD;
		else if (state == CONTRACT && (c < 'a' || 'z' < c))
			state = COUNTWRD;
		else if (state == COUNTLTR && c == '\'')
			state = CONTRACT;
		else if (state == COUNTWRD && (c < 'a' || 'z' < c))
			state = NONWORD;

		/* handle current state */

		if (state == COUNTLTR)
			++nc;
		else if (state == COUNTWRD || state == EOF) {
			if (nc <= MAXLEN)
				++nlen[(nc-1)];
			else
				++over;
			nc = 0;
			if (state == EOF)
				break;
		}

	}

	/* determine maximum words (including overflow) */

	max = 0;
	for (i = 0; i < MAXLEN; ++i)
		if (nlen[i] > max)
			max = nlen[i];
	if (over > max)
		max = over;

	/* determine scale */

	scale = 1;
	if (max > MAXBAR) {
		scale = (max / MAXBAR);
		if (max / scale > MAXBAR)
			++scale;
	}

	/* Find width */

	if (over > 0)
		width = MAXLEN;
	else {
		width = 0;
		for (j = 0; j < MAXLEN; ++j)
			if (nlen[j] > 0)
				width = (j + 1);
	}


     /* Print scaled vertical histogram */

	for (i = (max / scale) - 1; i >= 0; --i) {
		for (j = 0; j < width; ++j)
			if (i < (nlen[j] / scale))
				printf("*");
			else
				printf(" ");
		if (i < (over / scale))
			printf("*");
		else
			printf(" ");
		printf("\n");
	}

     /* Print vertical axis labels */

	for (i = 1; i <= width; ++i)
		printf("%d", (i / 10) % 10);
	if (over > 0)
		printf("%d", (MAXLEN / 10) % 10);
	printf("\n");

	for (i = 1; i <= width; ++i)
		printf("%d", i % 10);
	if (over > 0)
		printf("%d", MAXLEN % 10);
	printf("\n");

	for (i = 1; i <= width; ++i)
		printf(" ");
	if (over > 0)
		printf("+");
	printf("\n");

	/* print scale (with proper pluralization) */

	printf("\n'*' = %d word", scale);
	if (scale > 1)
		printf("s");
	printf("\n");

}
