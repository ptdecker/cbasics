/*
 * A version of getch() and ungetch() with only a single charater memory
 */

// Includes

#include <stdio.h>
#include <stdlib.h>

// Definitions

#define MAXSTR 100

// Globals

static char buffer = '\0'; // Single char buffer

/*
 * getch(): gets a character from the buffer
 */

static char getch(void) {
    char temp = buffer;
    if (buffer == '\0')
        temp = getchar();
    else
        buffer = '\0';
    return temp;
}

/*
 * ungetch(): ungets a character from the buffer
 */

static void ungetch(char c) {

    if (buffer != '\0') {
        printf("ungetch(): buffer overflow\n");
        exit(EXIT_FAILURE);
    }

    buffer = c;
}

/* Main */

int main(void) {

    char   s[MAXSTR]; // test string
    size_t i;         // string index
    char   c;         // last character read

    printf("Reading 10 characters from input...\n");
    i = 0;
    c = getch();
    while ((c = getch()) != EOF && i < 10)
        s[i++] = c;
    s[i] = '\0';
    printf("\t... result: \"%s\"\n", s);

    printf("Pushing back 1 character to input...\n");
    ungetch(s[--i]);
    s[i] = '\0';
    printf("\t... result: \"%s\"\n", s);

    printf("Reading 1 character from input...\n");
    s[i++] = getch();
    s[i] = '\0';
    printf("\t... result: \"%s\"\n", s);

    return 0;
}
