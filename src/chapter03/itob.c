/*
 * itob: converts an integer to a variable base character string representation
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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

static int strlen(const char *s) {
	const char *sc;
	for (sc = s; *sc != '\0'; ++sc)
		; // Empty
	return (sc - s);
}

/*
 * reverse(): reverse string 's' in place
 */

static void reverse(char s[]) {

	int c;
	int i;
	int j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c    = s[i];
		s[i] = s[j];
		s[j] = c;
	}

}

/*
 * iotb(): converts integer 'n' into a base 'b' string 's[]'
 */

static void itob(int n, char s[], int b) {

	int i = 0;
	int d;
	int sign;

	// Save the sign and make it positive if its negative
	sign = n;

	// generate digits in reverse order
	do {
		d = abs(n % b);                                          // gets the next digit
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