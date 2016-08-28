/*
 * getkeywords: counts the number of key words utilized within a C program
 */

/*@ -temptrans -nullret */

// Includes

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definitions

#define MAXSTACK      10  // Maximum characters parser can undo
#define MAXWORDSIZE   50  // Maximum number of characters in a word
#define KEY_NOT_FOUND EOF

// Globals

static char   buffer[MAXSTACK];   // Array-based buffer of char-typed values
static size_t bufferptr = 0;      // Buffer pointer--next free stack position

static struct key {
    char *word;
    int   count;
 } keytab[] = {
    {"auto",     0 },
    {"break",    0 },
    {"case",     0 },
    {"char",     0 },
    {"const",    0 },
    {"continue", 0 },
    {"default",  0 },
    {"do",       0 },
    {"double",   0 },
    {"else",     0 },
    {"enum",     0 },
    {"extern",   0 },
    {"float",    0 },
    {"for",      0 },
    {"goto",     0 },
    {"if",       0 },
    {"int",      0 },
    {"long",     0 },
    {"register", 0 },
    {"return",   0 },
    {"short",    0 },
    {"signed",   0 },
    {"sizeof",   0 },
    {"static",   0 },
    {"struct",   0 },
    {"switch",   0 },
    {"typedef",  0 },
    {"union",    0 },
    {"unsigned", 0 },
    {"void",     0 },
    {"volatile", 0 },
    {"while",    0 },
 };

static const size_t numkeys = (size_t)(sizeof keytab / sizeof(struct key));

/*
 * getch(): gets a character from the buffer
 */

static char getch(void) {
    return (bufferptr > 0) ? buffer[--bufferptr] : getchar();
}

/*
 * ungetch(): ungets a character from the buffer
 */

static void ungetch(char c) {

    if (bufferptr >= MAXSTACK) {
        printf("ungetch(): buffer overflow\n");
        exit(EXIT_FAILURE);
    }

    buffer[bufferptr++] = c;
}

/*
 * comment(): skip over a comment and return a character
 */

static char comment(void) {
    int c;
    while ((c = getch()) != EOF)
        if (c == '*') {
            if ((c = getch()) == '/')
                break;
            else
                ungetch(c);
        }

    return c;
}

/*
 * getword(): get next word or character from input making sure to properly handle underscores, string
 *            constants, comments, and pre-processor control lines.  Returns the first character of the word
 *            which would be '\0' or NULL if no word is returned.
 */

static char getword(char *word, int lim) {

    char  c;
    char  d;
    char *w = word;

    // Eat white space
    while (isspace(c = getch()))
        ; // Empty

    // Add character to the word buffer if we are not yet at EOF
    if (c != EOF)
        *w++ = c;

    // Handle text allowing for underscores and pre-processor control lines
    if (isalpha(c) || c == '_' || c == '#') {
        for ( ; --lim > 0; w++)
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }

    // Handle string and character constants
    } else if (c == '\'' || c == '\"') {
        for ( ; --lim > 0; w++)
            if ((*w = getch()) == '\\')
                *++w = getch();
            else if (*w == c) {
                w++;
                break;
            } else if (*w == EOF)
                break;

    // Handle comments (both block and line)
    } else if (c == '/') {
        if ((d = getch()) == '*') {
            c = comment();
        } else if (d == '/') {
            while ((c = getch()) != EOF && c != '\n')
                ; // Empty
        } else {
            ungetch(d);
        }
    }

    // Terminate our word buffer and return the first character
    *w = '\0';
    return c;
}

/*
 * binsearch(): find word in tab[0]...tab[n-1]
 */

static struct key *binsearch(char *word, struct key tab[], size_t n) {

    struct key *low  = &tab[0];
    struct key *high = &tab[n];
    int    cond = 0;

    while (low < high) {
        struct key *mid = low + (high - low) / 2;
        cond = strcmp(word, mid->word);
        if (cond < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;

    }

    return NULL;
};

/* Main */

int main(void) {

    char word[MAXWORDSIZE] = "";
    struct key *p;

    while (getword(word, MAXWORDSIZE) != EOF)
        if (isalpha(word[0]) && (p = binsearch(word, keytab, numkeys)) != NULL)
            p->count++;

    for (p = keytab; p < keytab + numkeys; p++)
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);

    return 0;
}
