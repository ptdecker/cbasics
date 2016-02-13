/*
 * Show tabs, backspaces, and backslashes
 */

#include <stdio.h>
#include <stdlib.h>

int main () {

    int c;

    while ((c = getchar()) != EOF)
        if (c == (int)'\t')
            printf("\\t");
        else if (c == (int)'\b')
            printf("\\b");
        else if (c == (int)'\\')
            printf("\\\\");
        else
            (void)putchar(c);

    exit(EXIT_SUCCESS);

}
