/*
 * Print a vertical histogram of word lengths
 */

#include <stdio.h>

#define MAXLEN   70  /* maximum word length to keep track of */
#define MAXBAR   16  /* maximum bar width */
#define NONWORD   0  /* "not in a word" state */
#define COUNTLTR  1  /* counting letters in a word state */
#define COUNTWRD  2  /* counting word lengths state */
#define CONTRACT  3  /* handling a contraction state */

int main() {

    /* initialize word length array */

    int nlen[MAXLEN];
    for (int i = 0; i < MAXLEN; ++i)
        nlen[i] = 0;

    /* count word lengths using a finite state machine */

    int c;
    int nc = 0;
    int over = 0;
    int state = NONWORD;

    while (1) {

        /* get character or EOF */

        c = getchar();

        /* convert uppercase characters to lowercase */

        if ('A' <= c && c <= 'Z')
            c = c - 'A' + 'a';

        /* handle state transitions */

        if (c == EOF) {
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

    int max = 0;
    for (int i = 0; i < MAXLEN; ++i)
        if (nlen[i] > max)
            max = nlen[i];
    if (over > max)
        max = over;

    /* determine scale */

    int scale = 1;
    if (max > MAXBAR) {
        scale = (max / MAXBAR);
        if (max / scale > MAXBAR)
           ++scale;
    }

    /* Find width */

    int width = 0;
    if (over > 0)
        width = MAXLEN;
    else
        for (int j = 0; j < MAXLEN; ++j)
            if (nlen[j] > 0)
                width = (j + 1);

     /* Print scaled vertical histogram */

    for (int i = (max / scale) - 1; i >= 0; --i) {
        for (int j = 0; j < width; ++j)
            putchar((i < (nlen[j] / scale)) ? '*' : ' ');
        putchar((i < (over / scale)) ? '*' : ' ');
    }

     /* Print vertical axis labels */

    for (int i = 1; i <= width; ++i)
        printf("%d", (i / 10) % 10);
    if (over > 0)
        printf("%d", (MAXLEN / 10) % 10);
    putchar('\n');

    for (int i = 1; i <= width; ++i)
        printf("%d", i % 10);
    if (over > 0)
        printf("%d", MAXLEN % 10);
    putchar('\n');

    for (int i = 1; i <= width; ++i)
        putchar(' ');
    if (over > 0)
        putchar('+');
    putchar('\n');

    /* print scale (with proper pluralization) */

    printf("\n'*' = %d word", scale);
    if (scale > 1)
        putchar('s');
    putchar('\n');

}
