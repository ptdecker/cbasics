/*
 * Replaces tabs with spaces up to set tab stops
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABSTOP 4

int main() {

    char c;
    int  ns = -1;
    int  numtabs;
    int  extraspace;

    while ((c = (char)getchar()) != (char)EOF)
        if ((c == ' ') && (ns > 0))
            ns++;
        else if (c == ' ')
            ns = 1;
        else if (ns > 0) {
            for (numtabs = ns / TABSTOP; numtabs > 0; numtabs--)
                (void)putchar('\t');
            for (extraspace = ns % TABSTOP; extraspace > 0; extraspace--)
                (void)putchar(' ');
            ns = -1;
            (void)putchar(c);
        } else
            (void)putchar(c);

    exit(EXIT_SUCCESS);
}
