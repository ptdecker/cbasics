/*
 * Display length of longest line
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 10000 /* Note: MAXLINE includes terminating newline and null characters */

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

/* copy: copy 'from' into 'to'; assume to is big enough */

static void copy(char to[], char from[]) {
    size_t i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

/* Main */

int main(void) {

    char   line[MAXLINE]   = "";
    char   longest[MAXLINE] = "";
    int    nl     = 0;
    size_t len    = 0;
    size_t maxlen = 0;

    while ((len = getbigline(line, MAXLINE)) > 0) {
        if (len > maxlen) {
            maxlen = len;
            copy(longest, line);
        }
        ++nl;
    }

    printf("%d line%s read.\n", nl, (nl == 1)?"":"s");
    if (nl > 0) {
        printf("The longest line is %u character%s long.\n", (unsigned)maxlen, (maxlen == 1) ? "" : "s");
        if (maxlen > MAXLINE) {
            printf("The first part of the longest line is: %s", longest);
        } else {
            printf("The longest line is: %s", longest);
        }
        (void)putchar('\n');
    }

    exit(EXIT_SUCCESS);
}
