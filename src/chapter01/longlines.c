/*
 * Prints any line equal to or larger than BIGLINE (up to MAXLINE)
 */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 10000 /* Note: MAXLINE includes terminating newline and null characters */
#define BIGLINE 80   /* Defines the minimum size of a line that will be printed */

/* getbigline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

static size_t getline(char s[], size_t lim) {

    char   c;
    size_t i = 0;

    while (--lim > 0 && (c = (char)getchar()) != (char)EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

/* Main */

int main(void) {

    char   line[MAXLINE] = "";
    size_t len = 0;

    while ((len = getline(line, MAXLINE)) > 0)
        if (len > BIGLINE)
            printf("%s", line);

    (void)putchar('\n');

    exit(EXIT_SUCCESS);
}


