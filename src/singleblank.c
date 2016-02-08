/*
 * Colapse two or more blanks with a single blank
 */

#include <stdio.h>

#define IN  1 /* inside a set of blanks */
#define OUT 0 /* outside a set of blanks */

int main () {

    int c;
    int state = OUT;

    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            state = OUT;
            putchar(c);
        } else if (state != IN) {
            state = IN;
            putchar(c);
        }
    }

}
