/*
* lexer.c
* 
* A trivial lexer that gets and operator or operand from standard input
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NUMBER '0'
#define NAME   'n'

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

	size_t i;
	char   c;

	// Get next character eating whitespace in the process

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		; //Empty

	s[1] = '\0';
	i = 0;

	// If it is a lower-case character it is a command or name, read it in

	if (isalpha(c)) {
		while (isalpha(s[++i] = c = getch()))
			; // Empty
		s[i] = '\0';
		if (c != EOF)      // More to read so push back last read
			ungetch(c);
		if (strlen(s) > 1)
			return NAME;   // Length > 1? then we have a name
		else
			return s[0];      // Else a command
	}

	// If the character is not part of a number or command (i.e. is an operator), return it

	if (!isdigit(c) && c != '.' &&  c != '-')
		return c;

	// Otherwise it is a number, read in the full number

	// Handle a negative sign
	// Look at next character to determine if '-' is a negative sign or
	// if it is the subtraction operator instead
	if (c == '-') {
		if (isdigit(c = getch()) || c == '.')
			s[++i] = c;
		else {
			if (c != (char)EOF)
				ungetch(c);
			return '-';
		}
	}

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