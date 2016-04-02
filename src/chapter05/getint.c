/*
* getint.c: Implements getint() that returns an integer from the input string
*
* NOTE: Also includes ability to sense integer number range limit overflows which the K&R
*       text does not call for but could be most helpful.
*/

//TODO: I don't really like how this approach handles EOF. For an input file that just has a number with
//      no end of line, just EOF, it returns an EOF status so no real way to know if a valid number
//      was found.

#include <ctype.h>
#include <limits.h>
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

static int getch(void) {
	return (bufferptr > 0) ? (int)buffer[--bufferptr] : getchar();
}

/*
 * ungetch(): ungets a character from the buffer
 */

static void ungetch(int c) {
	if (bufferptr >= MAXSTACK) {
		printf("ungetch(): buffer overflow\n");
		exit(EXIT_FAILURE);
	} else
		buffer[bufferptr++] = (char)c;
}

/*
 * getint(): gets an integer from the input string
 *
 * Returns:  EOF     if end of file
 *           0       if next input was not a number
 *           +       if input was a valid number
 *           INT_MAX if postive out of range was sensed
 *           INT_MIN if negative out of range was sensed
 */

static int getint(int *pn) {

	int c;
	int sign;
	int prior = 0;

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

	// Finally, read in the number itself

	*pn = 0;
	for (*pn = 0; isdigit(c); c = getch()) {
		prior = *pn;
		*pn = 10 * *pn + (c - (int)'0');
		// *pn should by definition be greater than prior, if we went negative than we overflowed
		if (*pn < prior) {
			return (sign > 0) ? INT_MAX : INT_MIN;
		}
	}

	// Finish off by applying the sign we saved earlier

	*pn *= sign;

	// So long as last thing we read was EOF, return the last thing we
	// read back to the input buffer so we can deal with it next however
	// we want.

	if (c != EOF)
		ungetch(c);

	return c;  // This could also return an EOF if we hit end of file with no number
}

int main(void) {
	int mynum = 0;
	switch (getint(&mynum)) {
		case EOF:
			printf("Reached end of file, number is: %d\n", mynum);
			break;
		case 0:
			printf("Next thing (besides whitespace) is not a number\n");
			break;
		case INT_MIN:
			printf("Negative range error\n");
			break;
		case INT_MAX:
			printf("Positive range error\n");
			break;
		default:
			printf("Number found: %d\n", mynum);
			break;
	}
	if (bufferptr > 0)
		printf("Input buffer contains: '%s'\n", buffer);
	exit(EXIT_SUCCESS);
}