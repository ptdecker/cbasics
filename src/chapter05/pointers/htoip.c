/*
 * Hexidecimal to integer converter (good to 32 bits)
 *
 * Pointer version
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static unsigned htoi(char *s) {

    int clower;
    int hexdigit = 0;
    unsigned n = 0;

    // Skip leading '0x' or '0X' if it is present

    if (*s == '0') {
        s++;
        if (tolower(*s) == 'x')
            s++;
    }

    // Convert remaining hex characters

    while (isxdigit(*s)) {
        clower = tolower(*s);
        hexdigit = (isdigit(clower)) ? *s - '0' : clower - 'a' + 10;
        n = (n << 4) + hexdigit;  // n << 4 equivalent to n * 16
        s++;
    }

    return n;
}

/* Main */

int main(void) {

    printf("FFFF converts to %u\n",   htoi("FFFF"));
    printf("0xFFFF converts to %u\n", htoi("0xFFFF"));
    printf("ABCD converts to %u\n",   htoi("ABCD"));
    printf("0xFFFFFFFF converts to %u\n", htoi("0xFFFFFFFF"));
    printf("converting an empty string yields %u\n", htoi(""));
    printf("0 converts to %u\n", htoi("0"));
    printf("0A converts to %u\n", htoi("0A"));

    return 0;
}
