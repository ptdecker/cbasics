// Includes

#include <stdio.h>

// Definitions

#define BIGSIZE 3000

/* Main */

int main(void) {

    int i;

    for(i = 0; i < BIGSIZE; ++i)
        (void)putchar(i % 10 + '0');

    (void)putchar('\n');

    return 0;
}


