/*
 * Hexidecimal to integer converter (good to 32 bits)
 */

// Includes

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * htoi(): Converts a hexadecimal string to an integer
 */

static unsigned int htoi(char s[]) {

    int      hexdigit = 0;
    int      i        = 0;
    bool     inhex    = true;
    unsigned n        = 0;

    // Skip leading '0x' or '0X' if it is present

    if (s[i] == '0') {
        i++;
        if (tolower(s[i]) == 'x')
            i++;
    }

    // Convert remaining hex characters

    for ( ; inhex; i++) {
        int clower = tolower(s[i]);
        if (isdigit(clower))
            hexdigit = s[i] - '0';
        else if ('a' <= clower && clower <= 'f')
            hexdigit = clower - 'a' + 10;
        else
            inhex = false;
        if (inhex)
            n = (n << 4) + hexdigit;  // n << 4 equivalent to n * 16
    }

    return n;
}

/* Main */

int main(void) {


    printf("FFFF converts to %u\n",   htoi("FFFF"));
    printf("0xFFFF converts to %u\n", htoi("0xFFFF"));
    printf("ABCD converts to %u\n", htoi("ABCD"));
    printf("0xFFFFFFFF converts to %u\n", htoi("0xFFFFFFFF"));
    printf("converting an empty string yields %u\n", htoi(""));

    return 0;
}
