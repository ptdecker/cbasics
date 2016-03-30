/*
 * itoarecursive: converts an integer to a character string (using a recursive approach)
 *
 * "Portions of this work are derived from The Standard C Library, copyright (c) 1992
 * by P.J. Plauger, published by Prentice-Hall, and are used with permission."
 *
 * NOTE:  The answer provided in "The C Answer Book" for this problem is simply wonderful
 *        and is faithfully reproduce here. Hard to improve upon perfection.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSTRING 256

/*
 * iota(): converts integer 'n' into a string 's[]' of minimum width 'w'
 */

static void itoa(int n, char s[]) {

	// Use a static variable within itoa to keep the running index. This
	// is initialized only when the program is initially loaded.  Every time
	// itoa() is run, it recurses down to the units case where it initializes
	// i back to zero. This is guaranteed to happen every time. Then, as the
	// calls resolve back up, i is incremented, the next digit is added to 
	// the string, and the terminator is moved one further in the string

	static int i = 0;

	if ((n / 10) != 0)
		// keep recursing down until we hit the units digit
		itoa(n / 10, s);
	else {
		// where at the units digit, so now set everything up
		// and handle our sign value
		i = 0;
		if (n < 0)
			s[i++] = '-';
	}

	// now get the digit value itself (ignoring sign) and 
	// set the terminator.  Note: "The C Answer Book" has a bug
	// in their solution.  They have "abs(n) % 10 + '0'" which 
	// does not work for the largest negative integer. The 
	// solution below works.
	s[i++] = (char)(abs(n % 10) + '0');
	s[i] = '\0';
}

int main(void) {
	int n;
	char s[MAXSTRING] = "";

	n = -234;
	itoa(n, s);
	printf("Number %d converted to a string is: \"%s\"\n", n, s);

	n = 1043;
	itoa(n, s);
	printf("Number %d converted to a string is: \"%s\"\n", n, s);

	n = INT_MIN;
	itoa(n, s);
	printf("Number %d converted to a string is: \"%s\"\n", n, s);

	exit(EXIT_SUCCESS);
}