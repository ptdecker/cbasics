/*
 * Print a vertical histogram of letter frequencies
 */

#include <stdio.h>

#define MAXLTRS  26  /* number of letters */
#define MAXBAR   18  /* maximum bar size */

int main() {

    /* initialize letter count array */

    int nltrs[MAXLTRS];
    for (int i = 0; i < MAXLTRS; ++i)
        nltrs[i] = 0;

    /* count letter frequencies (case insensitive) */

    int c;
    while ((c = getchar()) != EOF)
        if ('a' <= c && c <= 'z')
            ++nltrs[c-'a'];
        else if ('A' <= c && c <= 'Z')
            ++nltrs[c-'A'];

    /* find maximum letter count */

    int max = 0;
    for (int i = 0; i < MAXLTRS; ++i)
        if (nltrs[i] > max)
            max = nltrs[i];

    /* determine scale */

    int scale = 1;
    if (max > MAXBAR) {
        scale = (max / MAXBAR);
        if (max / scale > MAXBAR)
            ++scale;
    }

    /* print vertical histogram */

    for (int i = (max / scale) - 1; i >= 0; --i) {
        for (int j = 0; j < MAXLTRS; ++j)
            putchar((i < (nltrs[j] / scale)) ? '*' : ' ');
        putchar('\n');
    }

    /* print axis labels */

    for (int i = 0; i < MAXLTRS; ++i)
        putchar(i + 'A');
    putchar('\n');

    /* print scale */

    printf("\n'*' = %d letter", scale);
    if (scale > 1)
        putchar('s');
    putchar('\n');

}
