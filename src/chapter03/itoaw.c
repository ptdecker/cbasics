/*
 * itoa: converts an integer to a character string padded to a specific width
 *
 * "Portions of this work are derived from The Standard C Library, copyright (c) 1992
 * by P.J. Plauger, published by Prentice-Hall, and are used with permission."
 */

// Includes

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions

#define MAXSTRING 256

/*
 * reverse(): reverse string 's' in place
 */

static void reverse(char s[]) {

    size_t i;
    size_t j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char c;
        c    = s[i];
        s[i] = s[j];
        s[j] = c;
    }

}

/*
 * iota(): converts integer 'n' into a string 's[]' of minimum width 'w'
 */

static void itoa(int n, char s[], int w) {

    size_t i = 0;
    int    sign;

    // Save the sign and make it positive if its negative
    sign = n;

    // generate digits in reverse order
    do {
        s[i++] = (char)abs(n % 10) + '0'; // gets the next digit
    } while ((n /= 10) != 0);             // and deletes it from the number

    // set the sign of the string (again in reverse)
    if (sign < 0)
        s[i++] = '-';

    // if needed, add spaces to reach minimum width
    while (i < (size_t)w)
        s[i++] = ' ';

    // termerate the string
    s[i] = '\0';

    // and reverse the string back
    reverse(s);
}

/* Main */

int main(void) {

    int n;
    int w = 12;
    char s[MAXSTRING] = "";

    n = -234;
    itoa(n, s, w);
    printf("Number %d converted to a string of width %d is: \"%s\"\n", n, w, s);

    n = 1043;
    itoa(n, s, w);
    printf("Number %d converted to a string of width %d is: \"%s\"\n", n, w, s);

    n = INT_MIN;
    itoa(n, s, w);
    printf("Number %d converted to a string of width %d is: \"%s\"\n", n, w, s);

    return 0;
}
