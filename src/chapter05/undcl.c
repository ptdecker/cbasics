/*
*  dcl(): parses a C-style declartion
*/

// Library inclusions

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitinos

#define MAXOUTSTR 1000  // Maximum output string
#define MAXSTACK    10  // Maximum characters parser can undo
#define MAXTOKEN   100  // Maximum token size

// Enumerations

enum { NAME, PARENS, BRACKETS };

// Globals

int    tokentype;          // Type of last token
char   token[MAXTOKEN];    // Last token string
char   out[MAXOUTSTR];     // Output string
char   buffer[MAXSTACK];   // Array-based buffer of char-typed values
size_t bufferptr = 0;      // Buffer pointer--next free stack position
bool   prevtoken = false;  // Indicates if there is a previous token

/*
 * errmsg(): prints an error message
 */

void errmsg(char *msg) {
	printf("%s", msg);
	prevtoken = true;
}

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
	}
	
	buffer[bufferptr++] = (char)c;
}

/*
 * gettoken(): get a token
 */

int gettoken(void) {

	int   c;
	char *p = token;

	// Recover from error by returning prior token

	if (prevtoken) {
		prevtoken = false;
		return tokentype;
	}

	// Eat white space

	while ((c = getch()) == ' ' || c == '\t')
		;

	// If character is and open parentheses '(' then handle parentheses

	if (c == '(') {

		// Check and see if we have a close parentheses ')'

		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return (tokentype = PARENS);
		}
		
		ungetch(c);
		return (tokentype = '(');
	}

	// If character is an open bracket '[' then handle brackets

	if (c == '[') {

		// Copy characters from input to output until a closed bracket is reached
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';

		return (tokentype = BRACKETS);
	}
	
	// If character is an alphanumeric character

	if (isalpha(c)) {

		// Copy characters while we have letters and numbers
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';

		ungetch(c);
		return (tokentype = NAME);
	}

	return (tokentype = c);
}

/*
 * nexttoken():  look ahead to the next token then push it back
 */

int nexttoken(void) {

	int type;
	int prevtoken;

	type = gettoken();
	prevtoken = true;

	return type;
}

/*
 * main
 */

int main(void) {

	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				if ((type = nexttoken()) == PARENS || type == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
		printf("%s\n", out);
	}

	exit(EXIT_SUCCESS);
}