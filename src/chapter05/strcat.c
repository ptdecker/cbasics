/*
 * strcat.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSTR 1000

/*
 * strcat(): Concatenates string 'leftstring' to the end of 'rightstring' using a pointer-based
 *           implementation
 * NOTE: It is assumed that 'leftstring' is big enough to hold the combined text
 */

static void strcat(char *leftstr, char *rightstr) {
    while (*leftstr != '\0')
        leftstr++;
    while ((*leftstr++ = *rightstr++) != '\0')
        ; // Empty  
}


int main(void) {

    char string1[MAXSTR] = "This is the first string";
    char string2[MAXSTR] = "And this is a second";

    printf("Adding \"%s\" to the end of \"%s\" results in: ", string2, string1);

    strcat(string1, string2);

    printf("\"%s\"\n", string1);

    exit(EXIT_SUCCESS);
}
