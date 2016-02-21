/*
 * Count the blanks, tabs, and new lines from stdin
 *
 * NOTE: The casting of character literals to int is done to satisfy the
 *       requirements of linter (splint)
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

    int c;

    while ((c = getchar()) != EOF)
        if (c < 128)
            putchar(c);

    exit(EXIT_SUCCESS);
}
