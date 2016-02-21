/*
 * testupcase.c
 *
 * Tests an approach to converting uppercase characters to lowercase
 */

#include <stdio.h>

int main() {

    int i, c;

    i = 0;
    for (c = 32; c < 127; ++c) {
        i++;

        /* convert uppercase to lowercase */

        if ('A' <= c && c <= 'Z')
            c = c - 'A' + 'a';


        putchar(c);
        if (i % 16 == 0)
            putchar('\n');
    }

    putchar('\n');
}
