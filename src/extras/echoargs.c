/*
 * Echo passed arguments
 */

// Includes

#include <stdio.h>

/* Main */

int main (int argc, char *argv[]) {

    while (--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");

    (void)putchar('\n');

    return 0;
}
