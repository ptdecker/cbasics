/*
 * itob: converts an integer to a variable base character string representation
 *
 * Pointer version
 * 
 * "Portions of this work are derived from The Standard C Library, copyright (c) 1992
 * by P.J. Plauger, published by Prentice-Hall, and are used with permission."
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSTRING 256

/*
 * strlen(): returns the lenght of a string
 *
 * NOTE: Yes, I know, we could have used strlen() from the standard
 *       <string.h> C library... but, heck why import the whole library
 *       for one function? (Yes, true, if the compiler is good it should
 *       optimize all the stuff we shouldn't need)
 *
 * Source: "The Standard C Library", P.J. Plauger, p.403
 */

static size_t strlen(const char *s) {
	const char *sc;
	for (sc = s; *sc != '\0'; ++sc)
		; // Empty
	return (size_t)(sc - s);
}

/*
 * reverse(): reverse string 's' in place
 */

static void reverse(char *s) {
	char *j = s + strlen(s) - 1;
	while (s < j) {
		char  c;
		c    = *s;
		*s++ = *j;
		*j-- =  c;
	}
}

/*
 * iotb(): converts integer 'n' into a base 'b' string 's[]'
 */

static void itob(int n, char *s, int b) {

	char *sindex = s;
	int   sign   = n;  // Save the sign and make it positive if its negative

	// generate digits in reverse order
	do {
		int d = abs(n % b);                                         // gets the next digit
		*sindex++ = (d <= 9) ? (char)d + '0' : (char)d + 'A' - 10;  // save it as a char--letters if num > 9
	} while ((n /= b) != 0);                                        // and deletes it from the number

	// set the sign of the string (again in reverse)
	if (sign < 0)
		*sindex++ = '-';

	// termerate the string
	*sindex = '\0';

	// and reverse the string back
	reverse(s);
}

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

	exit(EXIT_SUCCESS);
}