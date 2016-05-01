/*
 * Remove trailing blanks and tabs from each line of input (up to MAXLINE characters)
 *
 * NOTE: Pointer version
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 // Note: MAXLINE includes terminating newline and null characters

/* getbigline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

static size_t getbigline(char *s, size_t lim) {

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

    while ((len = getbigline(line, MAXLINE)) > 0) {
        if (len != MAXLINE) {
            printf("%s", line);
        }
    }

    exit(EXIT_SUCCESS);
}

