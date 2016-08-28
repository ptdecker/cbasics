/*
 * lexer.c
 *
 * A trivial lexer that gets and operator or operand from standard input
 */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

// Includes

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Definitions

#define NUMBER  '0'
#define NAME    'n'
#define ERROR   '~'
#define MAXLINE 1000

// Globals

static char   line[MAXLINE] = "";
static char  *lineindex = line;

/*
 * getline(): gets a whole line into string 's' and returns the length
 */

static size_t getline(char s[], int maxlen) {

    int    c;
    size_t i = 0;

    while (--maxlen > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = (char)c;

    if (c == (int)'\n')
        s[i++] = (char)c;

    s[i] = '\0';

    return i;
}

/* getop(): gets the integer value of the next operator or numeric operand
 *
 * NOTE: Returns NUMBER if it is a number and the operand otherwise. If it is
 *       a number 's' contains the number upon return.
 */

char getop(char s[], double *val) {

    char token[MAXLINE] = "";
    char *t = token;

    // Get a line (if needed)

    if (*lineindex == '\0') {
        if (getline(line, MAXLINE) == 0)
            return EOF;
        else
            lineindex = line;
    }

    // Eat leading white space

    while (isspace(*lineindex))
        lineindex++;

    // Get next token from the line

    while (*lineindex != '\0' && !isspace(*lineindex)) {
        *t++ = *lineindex++;
    }
    *t = '\0';

    // End of line??

    if (*token == '\n' || *token == '\0')
        return '\n';

    // Try to read in a number from the token.  If successful, return the value and a NUMBER token

    if (sscanf(token, " %lf", val) == 1)
        return NUMBER;

    // Reading a number failed, try to read a string ... if it is a single character, return it;
    // otherwise, return a NAME token

    if (sscanf(token, " %s", s) == 1) {
        if (strlen(s) > 1)
            return NAME;
        else
            return s[0];
    }

    // Otherwise error out

    return ERROR;
}
