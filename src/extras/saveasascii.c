/*
 * Count the blanks, tabs, and new lines from stdin
 *
 * NOTE: The casting of character literals to int is done to satisfy the
 *       requirements of linter (splint)
 */

// Includes

#include <stdio.h>

/* Main */

int main(void) {

    int c;

    while ((c = getchar()) != EOF)
        if (c < 128)
            (void)putchar(c);

    return 0;
}
