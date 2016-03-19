/*
* lexer.c
* 
* A trivial lexer that gets and operator or operand from standard input
*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define NUMBER '0'

// External declariations

void capush(char);
char capop(void);
bool caempty(void);


/* getch(): gets a character either from the buffer or from stdin if buffer is empty */

static char getch(void) {
	return (caempty()) ? (char)getchar() : capop();
}

/* ungetch(): pushes a character onto the buffer */

static void ungetch(char ch) {
	capush(ch);
}

/* getop(): gets the integer value of the next operator or numeric operand
 *
 * NOTE: Returns NUMBER if it is a number and the operand otherwise. If it is
 *       a number 's' contains the number upon return.
 */

char getop(char s[]) {

	int i;
	char c;

	// Get next character eating whitespace in the process

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		; //Empty
	s[1] = '\0';

	// If the character is not part of a number (i.e. is an operator), return it

	if (!isdigit(c) && c != '.')
		return c;

	// Otherwise, read in the full number

	i = 0;
	// Read integer part
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			; // Empty
	// Read fractional part
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			; // Empty
	s[i] = '\0';

	if (c != (char)EOF)
		ungetch(c);

	return NUMBER;
}