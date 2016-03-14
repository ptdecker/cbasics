/*
 * rightrot
 *
 * Implements the rightor() function which returns the value of an integer 'x' rotated
 * right by 'n' bit positions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static int rightrot(int x, unsigned n) {
    int xrot;
    xrot = (int)((unsigned)x >> n);
    return xrot;
}

/*
 * printBits(): Helper function to display the bits in an unsigned integer
 */

static void printbits(unsigned x) {
    unsigned i;
    printf("0b");
    for(i = (unsigned)(8 * sizeof(int)); i > 0; i--)
        (bool)(x & (1 << (i - 1))) ? putchar('1') : putchar('0');
}

 int main() {

    int x;
    unsigned r;
    int xrot;

    x = 1212;
    r = 1;
    xrot = rightrot(x, r);
    printbits((unsigned)x);
    printf(" (%d) rotated %u to the right becomes\n", x, r);
    printbits((unsigned)xrot);
    printf(" (%d)\n\n", xrot);

    x = 3425;
    r = 5;
    xrot = rightrot(x, r);
    printbits((unsigned)x);
    printf(" (%d) rotated %u to the right becomes\n", x, r);
    printbits((unsigned)xrot);
    printf(" (%d)\n\n", xrot);

    x = -128;
    r = 2;
    xrot = rightrot(x, r);
    printbits((unsigned)x);
    printf(" (%d) rotated %u to the right becomes\n", x, r);
    printbits((unsigned)xrot);
    printf(" (%d)\n\n", xrot);


    exit(EXIT_SUCCESS);
 }
