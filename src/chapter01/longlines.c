/*
 * Prints any line equal to or larger than BIGLINE (up to MAXLINE)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* Note: MAXLINE includes terminating newline and null characters */
#define BIGLINE 80   /* Defines the minimum size of a line that will be printed */

/* getbigline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

static int getbigline(char s[], int lim) {

    char c;
    int  len = 0;
    int  slen = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (slen < (lim - 2))
            s[slen++] = c;
        ++len;
    }

    s[slen++] = '\n';
    s[slen] = '\0';

    return len;
}

/* Main */

int main() {

    char line[MAXLINE] = "";
    int len = 0;

    while ((len = getbigline(line, MAXLINE)) > 0)
        if (len > BIGLINE)
            printf("%s", line);

    exit(EXIT_SUCCESS);
}


