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
char   name[MAXTOKEN];     // Identifier name
char   datatype[MAXTOKEN]; // Data type ('char', 'int', etc)
char   out[MAXOUTSTR];     // Output string
char   buffer[MAXSTACK];   // Array-based buffer of char-typed values
size_t bufferptr = 0;      // Buffer pointer--next free stack position
bool   prevtoken = false;  // Indicates if there is a previous token

// Forward declarations

void dcl(void);

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
 * scompar(): implements strcmp in a way that is type compatible with bsearch
 */

int scompar(const void *str1, const void *str2) {
	return strcmp(str1, str2);
}

/*
 * typequal(): returns true if a token is a type-qualifier
 *
 * NOTE: since we are using bsearch to search typeq[], typeq[]'s' values must be in ascending order
 */

bool typequal(void) {

	static char *typeq[] = {
		"const",
		"volatile"
	};
	char *pt = token;

	return (bsearch(&pt, typeq, sizeof(typeq)/sizeof(char *), sizeof(char *), scompar) != NULL);
}

/*
 * typespec(): returns true if a token is a type-specifier
 *
 * NOTE: since we are using bsearch to search types[], types[]'s' values must be in ascending order
 */

bool typespec(void) {

	static char *types[] = {
		"char",
		"double",
		"float",
		"int",
		"long",
		"short",
		"signed",
		"unsigned",
		"void"
	};
	char *pt = token;

	return (bsearch(&pt, types, sizeof(types)/sizeof(char *), sizeof(char *), scompar) != NULL);
}

/*
 * dclspec(): interpret a declaration specification
 */

void dclspec(void) {

	char temp[MAXTOKEN];


	temp[0] = '\0';
	gettoken();
	do {
		if (tokentype != NAME) {
			prevtoken = true;
			dcl();
		} else if (typespec() || typequal()) {
			strcat(temp, " ");
			strcat(temp, token);
			gettoken();
		} else
			errmsg("unknown type in parameter list\n");

	} while (tokentype != ',' && tokentype != ')');
	strcat(out, temp);
	if (tokentype == ',')
		strcat(out, ",");
}

/*
 * parmdl(): parse a parameter declaration
 */

void parmdcl(void) {
	do {
		dclspec();
	} while (tokentype == ',');
	if (tokentype != ')')
		errmsg("missing ')' in parameter declaration\n");
}

/*
 * dirdcl(): parse a direct declarator
 */

void dirdcl(void) {

	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			errmsg("error: missing ')'\n");
	} else if (tokentype == NAME) {
		if (name[0] == '\0')
			strcpy(name, token);
	} else {
		prevtoken = true;
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == '(') {
			strcat(out, " function expecting");
			parmdcl();
			strcat(out, " and returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/*
 * dcl(): parse a declarator
 */

void dcl(void) {

	int ns; // number of asterisks

	for (ns = 0; gettoken() == '*'; )
		ns++;

	dirdcl();

	while (ns-- > 0)
		strcat(out, " pointer to");
}

/*
 * main
 */

int main(void) {

	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype != '\n') {
			printf("dcl: system error (end of line expected)\n");
			exit(EXIT_FAILURE);
		}
		printf("%s: %s %s\n", name, out, datatype);
	}

	exit(EXIT_SUCCESS);
}