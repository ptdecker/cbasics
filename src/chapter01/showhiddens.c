/*
 * Show tabs, backspaces, and backslashes
 */

#include <stdio.h>
#include <stdlib.h>

int main () {

    int c;

    while ((c = getchar()) != EOF)
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else
            (void)putchar(c);

    exit(EXIT_SUCCESS);

}
