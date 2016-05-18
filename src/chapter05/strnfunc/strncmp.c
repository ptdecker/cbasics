/*
 * strncmp.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSTR 1000

/*
 * strncmp(): Compares the fist 'count' characters of 'source' string to 'dest' string.
 *
 * NOTE: A terminating '\0' *is not* appended!
 * 
 * NOTE: It is assumed that 'leftstring' is big enough to hold the combined text
 */

static int strncmp(char *s1, char *s2, size_t count) {
    for ( ; --count > 0 && *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return *s1 - *s2;
}


int main(void) {

    char s1[MAXSTR] = "aaa";
    char s2[MAXSTR] = "aba";
    char s3[MAXSTR] = "abb";
    char s4[MAXSTR] = "aca";

    printf("Comparing the first 2 characters of \"%s\" to \"%s\" results in: %d\n", s1, s2, strncmp(s1, s2, 2));
    printf("Comparing the first 2 characters of \"%s\" to \"%s\" results in: %d\n", s3, s2, strncmp(s3, s2, 2));
    printf("Comparing the first 2 characters of \"%s\" to \"%s\" results in: %d\n", s4, s2, strncmp(s4, s2, 2));

    exit(EXIT_SUCCESS);
}
