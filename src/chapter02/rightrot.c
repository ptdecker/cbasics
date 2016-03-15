/*
 * rightrot
 *
 * Implements the rightror() function which returns the value of an integer 'x' rotated
 * right by 'n' bit positions.
 *
 * NOTE: My first solution to this confused rotation with shifting. When rotating right, the
 *       right most bit becomes the left most bit in the result.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * wordlength(): Helper fuction to determine the word length of the host
 */

static unsigned wordlength(void) {
    unsigned i;
    unsigned v;
    v = (unsigned)~0x00;
    for(i = 1; (v = v >> 1) > 0; i++)
        ;
    return i;
}

/*
 * rightrot(): Rotate x right by n bits (right most bit moves to left most position)
 */

static int rightrot(int x, unsigned n) {
    unsigned rbit; // Rightmost bit

    while (n-- > 0) {
        rbit = ((unsigned)x & 0x01) << (wordlength() - 1);
        x = (int)((unsigned)x >> 1);
        x = (int)((unsigned)x | rbit);
    }
    return x;
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


    x = 0xFA0A0A0A;
    r = 32;
    printbits((unsigned)x);
    printf(" (%d) rotated one time continuously for %u times to the right becomes:\n", x, r);
    while (r-- > 0) {
        xrot = rightrot(x, 1);
        printbits((unsigned)xrot);
        printf(" (%d)\n", xrot);
        x = xrot;
    }
    (void)putchar('\n');

    exit(EXIT_SUCCESS);
 }
