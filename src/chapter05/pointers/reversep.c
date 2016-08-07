/*
 * Reverses input lines one at a time
 *
 * Pointer version
 */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>

#define MAXLINE 10000 /* Note: MAXLINE includes terminating newline and null characters */

/* getbigline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

static size_t getline(char *s, size_t lim) {

    char c;
    char *sindex = s;

    while (--lim > 0 && (c = (char)getchar()) != (char)EOF && c != '\n')
        *sindex++ = c;
    if (c == '\n')
        *sindex++ = c;
    *sindex = '\0';

    return (size_t)(sindex - s);
}

/*
 * reverse: reverses a line
 */

static void reverse(char *s) {

    char *send   = s + strlen(s) - 1;

    // Leave terminating newline in place if they exist
    if (*send == '\n')
        --send;

    // Reverse remaining in place
    while (s < send) {
        char temp;
        temp    = *s;
        *s++    = *send;
        *send-- = temp;
    }
}

/* Main */

int main(void) {

    char   line[MAXLINE] = "";

    while (getline(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }
    (void)putchar('\n');

    return 0;
}
