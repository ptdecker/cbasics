/*
* getint.c: Implements getfloat() that returns a floating point from the input string
*
* NOTE: In addition, scientific notation is supported in the solution.
*/

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR   100
#define MAXSTACK 100 // Maximum depth of buffer (stack)

static size_t bufferptr = 0;    // Buffer pointer--next free stack position
static char   buffer[MAXSTACK]; // Array-based buffer of char-typed values

/*
 * getch(): gets a character from the buffer
 */

static char getch(void) {
	return (bufferptr > 0) ? buffer[--bufferptr] : getchar();
}

/*
 * ungetch(): ungets a character from the buffer
 */

static void ungetch(char c) {

	if (bufferptr >= MAXSTACK) {
		printf("ungetch(): buffer overflow\n");
		exit(EXIT_FAILURE);
	}
	
	buffer[bufferptr++] = c;
}

/*
 * getint(): gets a double floating point from the input string
 *
 * Returns:  EOF     if end of file
 *           0       if next input was not a number
 *           +       if input was a valid number
 */

static int getdouble(double *pn) {

	int c;
	int sign;
	double power = 1.0L;
	int sciexp = 1;

	// Skip white space

	while (isspace(c = getch()))
		; // Empty

	// See if we, perhaps, have a number
	// TODO: Returning zero doesn't seem like a great way to end if
	//       it turns out we're not dealing with a number

	if (!isdigit(c) && c != EOF && c != (int)'+' && c != (int)'-') {
		ungetch(c); // Not a number, so put it back into the input buffer
		return 0;   // Return zero to indicate no number was read
	}

	// Deal with negative numbers if we have a '-'

	sign = (c == (int)'-') ? -1 : 1;


	// And move on to the next character if we had a sign at all

	if (c == (int)'+' || c == (int)'-') {
		c = getch();
		// However, if what comes after the sign isn't a number, then
		// not a number so put both it and the sign back on the input buffer
		if (c == EOF)
			return c;
		if (!isdigit(c)) {
			ungetch(c);
			ungetch((sign < 0) ? '-' : '+');
			return 0;
		}
	}

	// Read in the natural number portion

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10L * *pn + (double)(c - (int)'0');


	// Read the fractional portion first skipping the '.' then proceeding if applicable

	if (c == '.') {
		c = getch();
		if (c == EOF)
			return c;
		for (power = 1L; isdigit(c); c = getch()) {
			*pn = 10L * *pn + (double)(c - (int)'0');
			power *= 10L;
		}
	}

	// Finish off by applying the sign we saved earlier

	*pn = sign * *pn / power;

	// Read the scientific notation portion if present
	if (c == 'e' || c == 'E') {
		c = getch();
		if (c == EOF)
			return c;
		sign = (c == '-') ? -1 : 1;
		if (c == '+' || c == '-')
			c = getch();
		if (c == EOF)
			return c;
		for (sciexp = 0; isdigit(c); c = getch())
			sciexp = 10 * sciexp + (int)(c - '0');
		if (sign == 1)
			while (sciexp-- > 0)
				*pn *= 10;
		else
			while (sciexp-- > 0)
				*pn /= 10;
	}

	// So long as last thing we read was EOF, return the last thing we
	// read back to the input buffer so we can deal with it next however
	// we want.

	if (c != EOF)
		ungetch(c);

	return c;  // This could also return an EOF if we hit end of file with no number
}

int main(void) {

	double mynum = 0L;
	int errcode = 0;

	errcode = getdouble(&mynum);

	if (errcode == EOF)
		printf("Reached end of file--number returned is: %g\n", mynum);
	else if (errcode == 0)
		printf("Next thing (besides whitespace) is not a number\n");
	else
		printf("Number found: %g\n", mynum);

	if (bufferptr > 0)
		printf("Input buffer contains: '%s'\n", buffer);

	exit(EXIT_SUCCESS);
}