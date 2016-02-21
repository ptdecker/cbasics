/*
 * Replaces tabs with spaces
 */

#include <stdio.h>
#include <stdlib.h>

#define TABSTOP 4

int main() {

    int c;
    int pos = 1;

    while ((c = getchar()) != EOF) {
        if (c == (int)'\t')
            for (int nb = TABSTOP - (pos - 1) % TABSTOP ; nb > 0; nb--, pos++)
                putchar(' ');
        else {
            putchar(c);
            pos = (c == (int)'\n' ? 1 : (pos + 1));
        }
    }

    exit(EXIT_SUCCESS);
}
