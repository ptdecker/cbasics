/*
* lexer.c
* 
* A trivial lexer that gets and operator or operand from standard input
*/

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NUMBER  '0'
#define NAME    'n'
#define MAXLINE 1000

static size_t lineindex     = 0;
static char   line[MAXLINE] = "";

/*
 * getline(): gets a whole line into string 's' and returns the length
 */

static size_t getline(char s[], int maxlen) {

	int    c;
	size_t i = 0;

	while (--maxlen > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = (char)c;

	if (c == (int)'\n')
		s[i++] = (char)c;

	s[i] = '\0';

	return i;
}

/* getop(): gets the integer value of the next operator or numeric operand
 *
 * NOTE: Returns NUMBER if it is a number and the operand otherwise. If it is
 *       a number 's' contains the number upon return.
 */

char getop(char s[]) {

	size_t i;
	char   c;

	// Read the next line of input

	if (line[lineindex] == '\0') {
		if (getline(line, MAXLINE) == 0)
			return EOF;
		else
			lineindex = 0;
	}

	// Get next character eating whitespace in the process

	while ((s[0] = c = line[lineindex++]) == ' ' || c == '\t')
		; //Empty

	s[1] = '\0';
	i = 0;

	// If it is a lower-case character it is a command or name, read it in

	if (islower(c)) {
		while (islower(s[++i] = c = line[lineindex++]))
			; // Empty
		s[i] = '\0';
		if (c != EOF)      // More to read so push back last read
			lineindex--;
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
		if (isdigit(c = line[lineindex++]) || c == '.')
			s[++i] = c;
		else {
			if (c != (char)EOF)
				lineindex--;
			return '-';
		}
	}

	// Read integer part
	if (isdigit(c))
		while (isdigit(s[++i] = c = line[lineindex++]))
			; // Empty
	// Read fractional part
	if (c == '.')
		while (isdigit(s[++i] = c = line[lineindex++]))
			; // Empty
	s[i] = '\0';

	if (c != (char)EOF)
		lineindex--;

	return NUMBER;
}