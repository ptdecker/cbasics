/*
 * invert
 *
 * Inverts the bits starting at a specified position
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned invert(unsigned x, unsigned  p, unsigned n) {
    unsigned adjusted;  // Adjusted position (accounting for size)
    unsigned mask;      // Mask [of sze n]
    adjusted = (p + 1 - n);
    mask = ~(~(unsigned)0 << n);  //results in a 000...000xxxx 32-bit mask with n number of x
    return x ^ (mask << adjusted);
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

int main(void) {

    printbits(0xA5A5);
    (void)putchar('\n');

    printbits(invert(0xA5A5, 7, 5));
    (void)putchar('\n');

    return 0;
}
