/*
 * fastbitcount
 *
 * Implements a fast version of bitcount().  bitcount() returns the number of 1-bits contained
 * within it's integer argument.  The fast version of it does this by using a two's complement
 * approach to delete the rightmost bit in 'x'.
 *
 * This approach uses 'x &= (x - 1)' to delete the rightmost bit in 'x'.
 *
 * To see how this works, let's work a few examples:
 *
 *     Say x = 275 which is '0b0000000100010011' assuming 16-bit word length.
 *
 *     x minus 1 is '0b0000000100010010' which, when ANDed with the above (which is what &= does), yields:
 *
 *                    x: 0b0000000100010011
 *                x - 1: 0b0000000100010010
 *                       ------------------
 *          x & (x - 1): 0b0000000100010010
 *
 *     Which has effectively deleted the rightmost bit of 'x'.
 *
 *     Another example where the rightmost bit is already zero:
 *
 *                    x: 0b0000001011100010 (738)
 *                x - 1: 0b0000001011100001
 *                       ------------------
 *          x & (x - 1): 0b0000001011100000
 *
 *      Which has also effectively deleted the rightmost bit of 'x'.
 *
 *      Let's try a negative number of -532.  532 is '0x0000001000010100'.  It's negative value in two's
 *      complement is 0x1111110111101100'. Therefore:
 *      
 *                    x: 0b1111110111101100 (-532)
 *                x - 1: 0b1111110111101011 (-533)
 *                       ------------------
 *          x & (x - 1): 0b1111110111101000
 *
 *       Which has also deleted the right most bit of 'x'
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define FAST 1  // Comment out to compile the slow version

/*
 * bitcount(): Returns the number of 1 bits in the integer 'x'
 *
 * NOTE: The slower version is included for comparision. In the worst case 
 *       condition where all bits of 'x' are one, the fast version will 
 *       take the same amount of time as the slow version. In all other
 *       cases, it will take less for it only requires as many iterations
 *       as are bits where as the slow version requires as many shifts as
 *       are needed to clear the left most bit.
 */

#ifdef FAST

    static unsigned bitcount(int x) {
        unsigned bits;
        unsigned ux;   // 'x' cast as an unsigned value
        ux = (unsigned)x;
        for (bits = 0; ux != 0; ux &= (ux - 1))
            bits++;
        return bits;
    }

#else

    static unsigned bitcount(int x) {
        unsigned bits;
        unsigned ux;   // 'x' cast as an unsigned value
        ux = (unsigned)x;
        for (bits = 0; ux != 0; ux >>= 1)
            if ((ux & 0x01) != 0)
                bits++;
        return bits;
    }

#endif

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

    x = 1212;
    printbits((unsigned)x);
    printf(" (%d) contains %u 1-bits\n", x, bitcount(x));

    x = 3425;
    printbits((unsigned)x);
    printf(" (%d) contains %u 1-bits\n", x, bitcount(x));

    x = -128;
    printbits((unsigned)x);
    printf(" (%d) contains %u 1-bits\n", x, bitcount(x));

    x = 0xFA0A0A0A;
    printbits((unsigned)x);
    printf(" (%d) contains %u 1-bits\n", x, bitcount(x));

    (void)putchar('\n');

    exit(EXIT_SUCCESS);
 }
