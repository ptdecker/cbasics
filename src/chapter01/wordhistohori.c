/*
 * Print a horizontal histogram of word lengths
 *
 * Utilizes a finite state machine to count words
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLEN   18  /* maximum word length to keep track of */
#define MAXBAR   60  /* maximum bar width */
#define NONWORD   0  /* "not in a word" state */
#define COUNTLTR  1  /* counting letters in a word state */
#define COUNTWRD  2  /* counting word lengths state */
#define CONTRACT  3  /* handling a contraction state */

int main() {

    int  i, j;
    char c;
    int  nc = 0;
    int  over = 0;
    int  state = NONWORD;
    int  nlen[MAXLEN];
    int  max = 0;
    int  scale = 1;

    for (i = 0; i < MAXLEN; ++i)
        nlen[i] = 0;

    while (true) {

        /* get character or EOF */

        c = (char)getchar();

        /* convert uppercase characters to lowercase */

        if ('A' <= c && c <= 'Z')
            c = c - 'A' + 'a';

        /* handle state transitions */

        if (c == (char)EOF) {
            state = EOF;
        } else if (state == NONWORD && 'a' <= c && c <= 'z') {
            state = COUNTLTR;
        } else if (state == NONWORD && (c < 'a' || 'z' < c)) {
            state = NONWORD;
        } else if (state == COUNTLTR && 'a' <= c && c <= 'z') {
            state = COUNTLTR;
        } else if (state == COUNTWRD && 'a' <= c && c <= 'z') {
            state = COUNTLTR;
        } else if (state == CONTRACT && 'a' <= c && c <= 'z') {
            state = COUNTLTR;
        } else if (state == COUNTLTR && (c < 'a' || 'z' < c)) {
            state = COUNTWRD;
        } else if (state == CONTRACT && (c < 'a' || 'z' < c)) {
            state = COUNTWRD;
        } else if (state == COUNTLTR && c == '\'') {
            state = CONTRACT;
        } else if (state == COUNTWRD && (c < 'a' || 'z' < c)) {
            state = NONWORD;
        }

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

    for (i = 0; i < MAXLEN; ++i)
        if (nlen[i] > max)
            max = nlen[i];
    if (over > max)
        max = over;

    /* determine scale */

    if (max > MAXBAR) {
        scale = (max / MAXBAR);
        if (max / scale > MAXBAR)
            ++scale;
    }

    /* print a scaled value-labled horizontal histogram */

    for (i = 0; i < MAXLEN; ++i) {
        printf(" %2d: ", (i + 1));
        for (j = 0; j < (nlen[i] / scale); ++j)
            (void)putchar('*');
        printf(" (%d)\n", nlen[i]);
    }

    /* print overflow scaled histogram bar */

    printf("%2d+: ", (MAXLEN + 1));
    for (i = 0; i < (over / scale); ++i)
        (void)putchar('*');
    printf(" (%d)\n", over);

    /* print scale (with proper pluralization) */

    printf("\n'*' = %d word", scale);
    if (scale > 1)
        (void)putchar('s');
    (void)putchar('\n');

    exit(EXIT_SUCCESS);
}
