/*
 * Display length of longest line
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* Note: MAXLINE includes terminating newline and null characters */

/*
 * getline(): read a line into s, return length
 */

static int getbigline(char s[], int lim) {
    int c = 0;
    int i = 0;
    while (i < lim - 1) {
        c = getchar();
        if (c == EOF)
            break;
        s[i] = c;
        i++;
        if (c == '\n')
            break;
    }
    s[i] = '\0';
    return i;
}

/*
 * copy(): copy 'from' into 'to'; assume to is big enough
 */

static void copy(char to[], char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

/* Main */

int main() {

    int len;
    int max = 0;
    char line[MAXLINE] = "";
    char longest[MAXLINE] = "";

    while ((len = getbigline(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)
        printf("%s", longest);

    exit(EXIT_SUCCESS);
}
