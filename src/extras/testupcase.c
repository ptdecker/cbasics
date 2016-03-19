/*
 * testupcase.c
 *
 * Tests an approach to converting uppercase characters to lowercase
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int i, c;

    i = 0;
    for (c = 32; c < 127; ++c) {
        i++;

        /* convert uppercase to lowercase */

        if ('A' <= c && c <= 'Z')
            c = c - 'A' + 'a';


        (void)putchar(c);
        if (i % 16 == 0)
            (void)putchar('\n');
    }

    (void)putchar('\n');

    exit(EXIT_SUCCESS);
}
