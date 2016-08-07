/*
 * Output one word per line
 */

#include <stdio.h>

#define IN  1  /* inside a word */
#define OUT 0  /* outside a word */

int main(void) {

    char c;             // current character
    int  inorout = OUT; // are we inside or outside of a word

    while ((c = getchar()) != EOF) {
        if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
            if (inorout == OUT)
                inorout = IN;
            (void)putchar(c);
        } else if ((c == ' ') || (c == '\n')) {
            if (inorout == IN)
                (void)putchar('\n');
            inorout = OUT;
        } else {
            // Ignore everything else (punctuation, special characters, etc)
        }
    }

    return 0;
}
