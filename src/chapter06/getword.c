/*
* getword(): get next word or character from input making sure to properly handle underscores, string
*            constants, comments, and pre-processor control lines
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Definitinos

#define MAXSTACK    10  // Maximum characters parser can undo
#define MAXWORDSIZE 50  // Maximum number of characters in a word

// Globals

static char   buffer[MAXSTACK];   // Array-based buffer of char-typed values
static size_t bufferptr = 0;      // Buffer pointer--next free stack position

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
 * comment(): skip over a comment and return a character
 */

static char comment(void) {

	int c;

	while ((c = getch()) != EOF)
		if (c == '*') {
			if ((c = getch()) == '/')
				break;
			else
				ungetch(c);
		}

	return c;
}

/*
 * getword(): get next word or character from input making sure to properly handle underscores, string
 *            constants, comments, and pre-processor control lines.  Returns the first character of the word
 *            which would be '\0' or NULL if no word is returned.
 */

static char getword(char *word, int lim) {

	char  c;
	char  d;
	char *w = word;

	// Eat white space
	while (isspace(c = getch()))
		; // Empty

	// Add character to the word buffer if we are not yet at EOF
	if (c != EOF)
		*w++ = c;

	// Handle text allowing for underscores and pre-processor control lines
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}

	// Handle string and character constants
	} else if (c == '\'' || c == '\"') {
		for ( ; --lim > 0; w++)
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c) {
				w++;
				break;				
			} else if (*w == EOF)
				break;

	// Handle comments (both block and line)
	} else if (c == '/') {
		if ((d = getch()) == '*') {
			c = comment();
		} else if (d == '/') {
			while ((c = getch()) != EOF && c != '\n')
				; // Empty
		} else {
			ungetch(d);
		}
	}

	// Terminate our word buffer and return the first character
	*w = '\0';
	return c;
}

/*
 * main:  a little test program for getword()
 */

int main(void) {

	char nextword[MAXWORDSIZE] = "";
	int  nextchar;

	while ((nextchar = getword(nextword, MAXWORDSIZE)) != EOF)
		if (isalnum(nextword[0]))
			printf("%s\n", nextword);

	return 0;
}

/* 
 * Below is a version of getword() that returns just words without the guard against underscores, string
 * constants, comments, and pre-processor control lines.  This might come in handy for other purposes where
 * one wants to pull just words out of stdin.

static char getword(char *word, int lim) {

	int   c;
	char *w = word;

	// Eat white space
	while (isspace(c = getch()))
		;

	// Add character to the word buffer if we are not yet at EOF
	if (c != EOF)
		*w++ = c;

	// If the character is not an word, then return it to the caller along with an empty word buffer
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	// Otherwise, read in characters until we have completed our word or our buffer limit is reached
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}

	// Terminate our word buffer and return the first character
	*w = '\0';
	return word[0];

}

 */