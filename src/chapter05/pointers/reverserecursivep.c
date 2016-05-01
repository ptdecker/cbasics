/*
 * Reverses input lines one at a time (using a recursive approach)
 *
 * Pointer version
 *
 * Note: "The C Answers" book does this with one less parameter passed to
 *       reversesub(). This approach certainly works but in my opinion is
 *       not as immediately understandable by a maintainer. Further, this
 *       solution still honors trying to preserve a trailing new line
 *       character.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 10000 /* Note: MAXLINE includes terminating newline and null characters */

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

/*
 * reversesub: reverses part of an array
 */

static void reversesub(char *s, char *send) {
    if (s < send) {
        char temp = *send;
        *send--   = *s;
        *s++      =  temp;
        reversesub(s, send);
    }
}

/*
 * reverse: reverses a line
 */

static void reverse(char *s) {
    char *send = s + strlen(s) - 1;
    reversesub(s, (*send == '\n') ? --send : send);
}

/* Main */

int main(void) {
    char line[MAXLINE] = "";
    while (getbigline(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }
    (void)putchar('\n');
    exit(EXIT_SUCCESS);
}
