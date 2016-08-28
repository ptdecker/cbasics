/*
 * itob: converts an integer to a variable base character string representation
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
        int c;
        c    = s[i];
        s[i] = s[j];
        s[j] = c;
    }

}

/*
 * iotb(): converts integer 'n' into a base 'b' string 's[]'
 */

static void itob(int n, char s[], int b) {

    size_t i    = 0;
    int    sign = n; // Save the sign and make it positive if its negative

    // generate digits in reverse order
    do {
        int d = abs(n % b);                                      // gets the next digit
        s[i++] = (d <= 9) ? (char)d + '0' : (char)d + 'A' - 10;  // save it as a char--letters if num > 9
    } while ((n /= b) != 0);                                     // and deletes it from the number

    // set the sign of the string (again in reverse)
    if (sign < 0)
        s[i++] = '-';

    // termerate the string
    s[i] = '\0';

    // and reverse the string back
    reverse(s);
}

/* Main */

int main(void) {
    int n;
    int b;
    char s[MAXSTRING] = "";

    n = -255;
    b = 10;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 2;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 8;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 16;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    (void)putchar('\n');

    n = 255;
    b = 10;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 2;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 8;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 16;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    (void)putchar('\n');

    n = 1043;
    b = 10;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 2;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 8;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 16;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    (void)putchar('\n');

    n = INT_MIN;
    b = 10;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 2;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 8;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);
    b = 16;
    itob(n, s, b);
    printf("Number %d converted to a string in base %d is: \"%s\"\n", n, b, s);

    return 0;
}
