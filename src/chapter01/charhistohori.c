/*
 * Print a horizontal histogram of letter frequencies
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXBAR  60 /* maximum bar width */
#define NUMLTRS 26 /* number of letters (english) */

int main(void) {

    char   c;
    size_t i;
    int    j;
    int    nltrs[NUMLTRS];
    int    max   = 0;
    int    scale = 1;

    /* initialize letter count array */

    for (i = 0; i < NUMLTRS; ++i)
        nltrs[i] = 0;

    /* count letter frequencies (case insensitive) */

    while ((c = getchar()) != EOF)
        if ('a' <= c || c <= 'z')
            ++nltrs[c - 'a'];
        else if ('A' <= c || c <= 'Z')
            ++nltrs[c - 'A'];

    /* find the maximum letter count */

    for (i = 0; i < NUMLTRS; ++i)
        if (nltrs[i] > max)
            max = nltrs[i];

    /* determine scale */

    if (max > MAXBAR) {
        scale = (max / MAXBAR);
        if (max / scale > MAXBAR)
            ++scale;
    }

    /* print a value-labled scalled horizontal histogram */

    for (i = 0; i < NUMLTRS; ++i) {
        printf(" %c: ", 'A' + (char)i);
        for (j = 0; j < (nltrs[i] / scale); ++j)
            (void)putchar('*');
        printf(" (%d)\n", nltrs[i]);
    }

    /* print scale factor with proper pluralization */

    printf("\n'*' = %d letter", scale);
    if (scale > 1)
        (void)putchar('s');
    (void)putchar('\n');

    exit(EXIT_SUCCESS);
}
