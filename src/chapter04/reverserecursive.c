/*
 * Reverses input lines one at a time (using a recursive approach)
 *
 * Note: "The C Answers" book does this with one less parameter passed to
 *       reversesub(). This approach certainly works but in my opinion is
 *       not as immediately understandable by a maintainer. Further, this
 *       solution still honors trying to preserve a trailing new line
 *       character.
 */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
 * reversesub: reverses part of an array
 */

static void reversesub(char s[], size_t start, size_t end) {
    if (start < end) {
        char temp = s[end];
        s[end] = s[start];
        s[start] = temp;
        reversesub(s, ++start, --end);
    }
}

/*
 * reverse: reverses a line
 */

static void reverse(char s[]) {
    size_t i = (strlen(s) - 1);
    reversesub(s, 0, (s[i] == '\n') ? --i : i);
}

/* Main */

int main(void) {
    char line[MAXLINE] = "";
    while (getline(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }
    (void)putchar('\n');
    exit(EXIT_SUCCESS);
}
