/*
 * Show tabs, backspaces, and backslashes
 */

// Includes

#include <stdio.h>

/* Main */

int main(void) {

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

    return 0;
}
