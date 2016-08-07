/*
 * Count the blanks, tabs, and new lines from stdin
 *
 * NOTE: The casting of character literals to int is done to satisfy the
 *       requirements of linter (splint)
 */

#include <stdio.h>

int main(void) {

    int c;

    while ((c = getchar()) != EOF)
        if (c < 128)
            (void)putchar(c);

    return 0;
}
