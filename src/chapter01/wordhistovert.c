/*
 * Print a vertical histogram of word lengths
 *
 * Utilizes a finite state machine to count words
 */

#include <stdbool.h>
#include <stdio.h>

#define MAXLEN   70  /* maximum word length to keep track of */
#define MAXBAR   16  /* maximum bar width */
#define NONWORD   0  /* "not in a word" state */
#define COUNTLTR  1  /* counting letters in a word state */
#define COUNTWRD  2  /* counting word lengths state */
#define CONTRACT  3  /* handling a contraction state */

int main(void) {

    size_t i;
    int    j;
    char   c;
    size_t nc    = 0;
    int    over  = 0;
    int    state = NONWORD;
    int    max   = 0;
    int    scale = 1;
    int    width = 0;
    int    nlen[MAXLEN];

    for (i = 0; i < MAXLEN; ++i)
        nlen[i] = 0;

    while (true) {

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

    /* Find width */

    if (over > 0)
        width = MAXLEN;
    else
        for (j = 0; j < MAXLEN; ++j)
            if (nlen[j] > 0)
                width = (j + 1);

     /* Print scaled vertical histogram */

    for (i = (size_t)(max / scale); i > 0; --i) {
        for (j = 0; j < width; ++j)
            if (i <= (size_t)(nlen[j] / scale))
                (void)putchar('*');
            else
                (void)putchar(' ');
        if (i <= (size_t)(over / scale))
            (void)putchar('*');
        else
            (void)putchar(' ');
        (void)putchar('\n');
    }

     /* Print vertical axis labels */

    for (i = 1; i <= (size_t)width; ++i)
        printf("%u", ((unsigned)i / 10) % 10);
    if (over > 0)
        printf("%d", (MAXLEN / 10) % 10);
    (void)putchar('\n');

    for (i = 1; i <= (size_t)width; ++i)
        printf("%u", (unsigned)i % 10);
    if (over > 0)
        printf("%d", MAXLEN % 10);
    (void)putchar('\n');

    for (i = 1; i <= (size_t)width; ++i)
        (void)putchar(' ');
    if (over > 0)
        (void)putchar('+');
    (void)putchar('\n');

    /* print scale (with proper pluralization) */

    printf("\n'*' = %d word", scale);
    if (scale > 1)
        (void)putchar('s');
    (void)putchar('\n');

    return 0;
}
