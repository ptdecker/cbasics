/*
 * Remove trailing blanks and tabs from each line of inputh (up to MAXLINE characters)
 */

#include <stdio.h>

#define MAXLINE 1000 /* Note: MAXLINE includes terminating newline and null characters */

/* Functional prototypes */

int getbigline(char line[], int maxline);

/* Main */

int main() {

    char line[MAXLINE];

    int len = 0;
    while ((len = getbigline(line, MAXLINE)) > 0) {
        if (len > MAXLINE) {
            printf("%s", line);
        }
    }
}

/* getbigline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

int getbigline(char s[], int lim) {

    int c;
    int len = 0;
    int slen = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (slen < (lim - 2)) {
            s[slen++] = c;
        }
        ++len;
    }

    s[slen++] = '\n';
    s[slen] = '\0';

    return len;
}
