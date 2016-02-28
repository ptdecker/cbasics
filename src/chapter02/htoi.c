/*
 * Hexidecimal to integer converter (good to 32 bits)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

static unsigned int htoi(char s[]) {

    int  hexdigit = 0;
    int  i = 0;
    int  clower;
    bool inhex = true;
    unsigned int n = 0;

    // Skip leading '0x' or '0X' if it is present

    if (s[i] == '0') {
        i++;
        if (tolower(s[i]) == 'x')
            i++;
    }

    // Convert remaining hex characters

    for ( ; inhex; i++) {
        clower = tolower(s[i]);
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

int main() {


    printf("FFFF converts to %u\n",   htoi("FFFF"));
    printf("0xFFFF converts to %u\n", htoi("0xFFFF"));
    printf("ABCD converts to %u\n", htoi("ABCD"));
    printf("0xFFFFFFFF converts to %u\n", htoi("0xFFFFFFFF"));
    printf("converting an empty string yields %u\n", htoi(""));

    exit(EXIT_SUCCESS);
}
