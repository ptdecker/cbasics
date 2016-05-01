/*
 * Display length of longest line
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 10000 /* Note: MAXLINE includes terminating newline and null characters */

/*
 * getline(): read a line into s, return length
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

/*
 * copy(): copy 'from' into 'to'; assume to is big enough
 */

static void copy(char to[], char from[]) {
    size_t i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

/* Main */

int main(void) {

    size_t len;
    size_t max = 0;
    char   line[MAXLINE] = "";
    char   longest[MAXLINE] = "";

    while ((len = getbigline(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)
        printf("%s", longest);

    exit(EXIT_SUCCESS);
}
