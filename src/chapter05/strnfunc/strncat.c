/*
 * strncat.c
 */

/*@ -shadow */

// Includes

#include <stdbool.h>
#include <stdio.h>

// Definitions

#define MAXSTR 1000

/*
 * strncat(): Concatenates string 'leftstring' to the end of 'rightstring' using a pointer-based
 *           implementation. Concatinates, at most, 'rcount' characters of 'rightstring'
 * NOTE: It is assumed that 'leftstring' is big enough to hold the combined text
 */

static void strncat(char *leftstr, char *rightstr, size_t rcount) {
    while (*leftstr != '\0')
        leftstr++;
    while (rcount-- > 0 && (*leftstr++ = *rightstr++) != '\0')
        ; // Empty
    *leftstr = '\0';
}

/* Main */

int main(void) {

    char string1[MAXSTR] = "This is the first string";
    char string2[MAXSTR] = "And this is a second";

    printf("Adding the first 5 characters of \"%s\" to the end of \"%s\" results in: ", string2, string1);

    strncat(string1, string2, 5);

    printf("\"%s\"\n", string1);

    return 0;
}
