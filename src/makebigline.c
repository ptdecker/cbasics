#include <stdio.h>

#define BIGSIZE 3000

int main() {

    int i;

    for(i = 0; i < BIGSIZE; ++i)
        putchar(i % 10 + '0');

    putchar('\n');

}


