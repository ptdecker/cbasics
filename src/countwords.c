/*
 * Count words
 */

#include <stdio.h>

#define IN  1  /* inside a word */
#define OUT 0  /* outside a word */

int main() {

    int c;             // current character
    int inorout = OUT; // are we inside or outside of a word
    int words   = 0;   // number of words

    while ((c = getchar()) != EOF) {
        if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
            if (inorout == OUT) {
                inorout = IN;
                words++;
            }
        } else if ((c == ' ') || (c == '\n')) {
            inorout = OUT;
        } else {
            // Ignore everything else (punctuation, special characters, etc)
        }
    }

    printf("%d\n", words);
}
