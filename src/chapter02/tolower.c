/*
 * lower()
 */

// Includes

#include <stdio.h>

/*
 * lower(): Converts a character to lower space
 */

static char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

/* Main */

int main(void) {

    (void)putchar(lower('T'));
    (void)putchar(lower('t'));
    (void)putchar('\n');

    return 0;
}
