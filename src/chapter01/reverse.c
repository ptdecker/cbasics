/*
 * Reverses input lines one at a time
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* Note: MAXLINE includes terminating newline and null characters */

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

/*
 * reverse: reverses a line
 */

static void reverse(char s[], int length) {

    char temp;
    int i;

    for (i = 0; i < (length - i - 1); i++) {
        temp = s[i];
        s[i] = s[length - i - 1];
        s[length - i - 1] = temp;
    }
}

/* Main */

int main(void) {

    char line[MAXLINE] = "";
    int len = 0;

    while ((len = getbigline(line, MAXLINE)) > 0) {
        reverse(line, len);
        printf("%s", line);
    }

    exit(EXIT_SUCCESS);
}


