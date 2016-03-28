/*
 * itoa: converts an integer to a character string padded to a specific width
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

static void reverse(char s[]) {

	char   c;
	size_t i;
	size_t j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
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

	exit(EXIT_SUCCESS);
}