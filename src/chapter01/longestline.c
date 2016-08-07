/*
 * Display length of longest line
 */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L


#include <stdio.h>

#define MAXLINE 10000 /* Note: MAXLINE includes terminating newline and null characters */

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

/* copy: copy 'from' into 'to'; assume to is big enough */

static void copy(char to[], char from[]) {

    size_t i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}

/* Main */

int main(void) {

    char   line[MAXLINE]    = "";
    char   longest[MAXLINE] = "";
    int    nl     = 0;
    size_t len    = 0;
    size_t maxlen = 0;

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > maxlen) {
            maxlen = len;
            copy(longest, line);
        }
        ++nl;
    }

    printf("%d line%s read.\n", nl, (nl == 1)?"":"s");
    if (nl > 0) {
        printf("The longest line is %u character%s long.\n", (unsigned)maxlen, (maxlen == 1) ? "" : "s");
        printf("The %slongest line is: %s\n", (maxlen > MAXLINE) ? "first part of the " : "", longest);
    }

    return 0;
}
