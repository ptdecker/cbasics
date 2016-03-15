/*
 * lower()
 */

#include <stdlib.h>
#include <stdio.h>

/*
 * lower(): Converts a character to lower space
 */

static char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}


int main() {

    (void)putchar(lower('T'));
    (void)putchar(lower('t'));
    (void)putchar('\n');

    exit(EXIT_SUCCESS);
}
