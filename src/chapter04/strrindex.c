/*
 * strrindex: Returns the position of the rightmost occurrence of t in s
 *
 * Returns the position of the rightmost occurrence of 't' inside 's' or -1 if
 * not found.
 */

// Includes

#include <stdio.h>
#include <string.h>

// Definitions

#define NOT_FOUND -1
#define MAX_STRING 100

/*
 * strindex(): Returns index of leftmost 't' inside 's' or -1 if not found
 */

static int strindex(char s[], char t[]) {

    size_t i;
    size_t j;
    size_t k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ; // Empty
        if (k > 0 && t[k] == '\0')
            return (int)i;
    }

    return NOT_FOUND;
}

/*
 * strrindex(): Returns index of rightmost 't' inside 's' or -1 if not found
 *
 * Note: The (i - 1) expression is used to adjust for counting down on an unsigned
 * type (size_t) which cannot go negative so the traditional test of "i >= 0" for
 * completion will not work.
 */

static int strrindex(char s[], char t[]) {

    size_t i;
    size_t j;
    size_t k;

    for (i = (strlen(s) - strlen(t) + 1); i > 0; i--) {
        for (j = (i - 1), k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ; // Empty
        if (k > 0 && t[k] == '\0')
            return (int)(i - 1);
    }

    return NOT_FOUND;
}

/* Main */

int main(void) {

    char s[] = "This is my test string, but its not much of a test string.";
    char t[MAX_STRING] = "";

    (void)strcpy(t, "test");
    printf("In the string: \"%s\"\n", s);
    printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
    printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));
    (void)putchar('\n');

    (void)strcpy(t, "string");
    printf("In the string: \"%s\"\n", s);
    printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
    printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));
    (void)putchar('\n');

    (void)strcpy(t, "This");
    printf("In the string: \"%s\"\n", s);
    printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
    printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));
    (void)putchar('\n');

    (void)strcpy(t, ".");
    printf("In the string: \"%s\"\n", s);
    printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
    printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));
    (void)putchar('\n');

    (void)strcpy(t, "not in string");
    printf("In the string: \"%s\"\n", s);
    printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
    printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));

    return 0;
}
