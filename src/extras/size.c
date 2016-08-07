/*
 * Count the blanks, tabs, and new lines from stdin
 *
 * NOTE: The casting of character literals to int is done to satisfy the
 *       requirements of linter (splint)
 */

#include <stdio.h>

int main(void) {

    int c;
    int size = 0;

    while ((c = getchar()) != EOF)
        size++;

    printf("%d\n", size);

    return 0;
}
