/*
 * Prints any line equal to or larger than BIGLINE (up to MAXLINE)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 10000 /* Note: MAXLINE includes terminating newline and null characters */
#define BIGLINE 80   /* Defines the minimum size of a line that will be printed */

/* getbigline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

static size_t getbigline(char s[], size_t lim) {

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

    while ((len = getbigline(line, MAXLINE)) > 0)
        if (len > BIGLINE)
            printf("%s", line);

    (void)putchar('\n');

    exit(EXIT_SUCCESS);
}


