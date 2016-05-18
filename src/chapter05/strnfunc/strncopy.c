/*
 * strncopy.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSTR 1000

/*
 * strncopy(): Copies at most 'count' characters of 'source' string to 'dest' string.
 *
 * NOTE: A terminating '\0' *is not* appended!
 * 
 * NOTE: It is assumed that 'leftstring' is big enough to hold the combined text
 */

static void strncopy(char *dest, char *source, size_t count) {
    while (count-- > 0 && (*dest++ = *source++) != '\0')
        ; // Empty
}


int main(void) {

    char string1[MAXSTR] = "Overwrite me!!";
    char string2[MAXSTR] = "I am the destoryer!";

    printf("Copies the first 4 characters of \"%s\" to the string currently containing \"%s\" results in: ", string2, string1);

    strncopy(string1, string2, 4);

    printf("\"%s\"\n", string1);

    exit(EXIT_SUCCESS);
}
