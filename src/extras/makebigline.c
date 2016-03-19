#include <stdio.h>
#include <stdlib.h>

#define BIGSIZE 3000

int main(void) {

    int i;

    for(i = 0; i < BIGSIZE; ++i)
        (void)putchar(i % 10 + '0');

    (void)putchar('\n');

    exit(EXIT_SUCCESS);
}


