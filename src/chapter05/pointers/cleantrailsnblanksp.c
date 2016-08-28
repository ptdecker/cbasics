/*
 * Remove trailing blanks and tabs from each line of input (up to MAXLINE characters)
 *
 * NOTE: Pointer version
 */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

// Includes

#include <stdio.h>

// Definitions

#define MAXLINE 1000 // Note: MAXLINE includes terminating newline and null characters

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

/* Main */

int main(void) {

    char   line[MAXLINE] = "";
    size_t len = 0;

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len != MAXLINE) {
            printf("%s", line);
        }
    }

    return 0;
}

