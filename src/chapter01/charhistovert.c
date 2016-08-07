/*
 * Print a vertical histogram of letter frequencies
 */

#include <stdio.h>

#define MAXLTRS  26  /* number of letters */
#define MAXBAR   18  /* maximum bar size */

int main(void) {

    char   c;
    size_t i;
    int    j;
    int    nltrs[MAXLTRS];
    int    max   = 0;
    int    scale = 1;

    /* initialize letter count array */

    for (i = 0; i < MAXLTRS; ++i)
        nltrs[i] = 0;

    /* count letter frequencies (case insensitive) */

    while ((c = getchar()) != EOF)
        if ('a' <= c && c <= 'z')
            ++nltrs[c - 'a'];
        else if ('A' <= c && c <= 'Z')
            ++nltrs[c - 'A'];

    /* find maximum letter count */

    for (i = 0; i < MAXLTRS; ++i)
        if (nltrs[i] > max)
            max = nltrs[i];

    /* determine scale */

    if (max > MAXBAR) {
        scale = (max / MAXBAR);
        if (max / scale > MAXBAR)
            ++scale;
    }

    /* print vertical histogram */

    for (i = (size_t)(max / scale); i > 0; --i) {
        for (j = 0; j < MAXLTRS; ++j)
            if (i <= (size_t)(nltrs[j] / scale))
                (void)putchar('*');
            else
                (void)putchar(' ');
        (void)putchar('\n');
    }

    /* print axis labels */

    for (i = 0; i < MAXLTRS; ++i)
        (void)putchar((char)i + 'A');
    (void)putchar('\n');

    /* print scale */

    printf("\n'*' = %d letter", scale);
    if (scale > 1)
        (void)putchar('s');
    (void)putchar('\n');

    return 0;
}
