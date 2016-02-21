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
    int blanks = 0;
    int tabs   = 0;
    int nl     = 0;

    while ((c = getchar()) != EOF)
        if (c == (int)' ')
            ++blanks;
        else if (c == (int)'\t')
            ++tabs;
        else if (c == (int)'\n')
            ++nl;

    printf("%d blanks, %d tabs, %d newlines\n", blanks, tabs, nl);

    exit(EXIT_SUCCESS);
}
