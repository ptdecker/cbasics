/*
 * Remove trailing blanks and tabs from each line of inputh (up to MAXLINE characters)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 // Note: MAXLINE includes terminating newline and null characters

/* getbigline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

size_t getbigline(char s[], size_t lim) {

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
        if (len > MAXLINE)
            printf("%s", line);

    exit(EXIT_SUCCESS);
}

