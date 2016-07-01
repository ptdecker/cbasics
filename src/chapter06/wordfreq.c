/*
* wordfreq(): Lists all the distinct words from stdin listed in decreasing frequency
*
* NOTE:  This solution leverages an implementation of sorting a singly linked list
*        from here:  http://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions

#define MAXSTACK      10    // Maximum characters parser can undo
#define MAXWORDSIZE   50    // Maximum number of characters in a word

// Globals

static char   buffer[MAXSTACK];   // Array-based buffer of char-typed values
static size_t bufferptr = 0;      // Buffer pointer--next free stack position

// Structures

struct tnode {
	char *word;           // Points to the text stored in the node
	int  count;           // Number of occurances of the word
	struct tnode *left;   // Left child
	struct tnode *right;  // Right child
};

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
 * getword(): get next word or character from input
 */

static char getword(char *word, int lim) {

	int   c;
	char *w = word;

	// Eat white space excepting line breaks
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
	// Allow for single quotes and hyphens within the word.
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '\'' && *w != '-') {
			ungetch(*w);
			break;
		}

	// Terminate our word buffer and return the first character
	*w = '\0';
	return word[0];

}

/*
 * talloc(): make a tnode
 */

static struct tnode *talloc(void) {

	struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));

	if (p == NULL) {
		printf("Error: ran out of memory");
		exit(EXIT_FAILURE);
	}

	return p;
} 

/*
 * strdup(): make a duplicate copy of s
 */

static char *mystrdup(char *s) {

	char *p = (char *)malloc(strlen(s) + 1);

	if (p == NULL) {
		printf("Error: ran out of memory");
		exit(EXIT_FAILURE);
	}

	strcpy(p, s);
	return p;
}

/*
 * treeadd(): add a node to our tree
 */

static struct tnode *treeadd(struct tnode *p, char *w) {

	int cond;

	if (p == NULL) {
		p = talloc();
		p->word  = mystrdup(w);
		p->count = 1;
		p->right = NULL;
		p->left  = NULL;
	} else if ((cond = strncmp(w, p->word, MAXWORDSIZE)) == 0)
		p->count++;
	else if (cond < 0)
		p->left  = treeadd(p->left, w);
	else
		p->right = treeadd(p->right, w);

	return p;
}

/*
 * treeprint: traverse the tree in order and print node if p->match is true
 */

static void treeprint(struct tnode *p) {

	if (p != NULL) {
		treeprint(p->left);
		printf("%5d %s\n", p->count, p->word);
		treeprint(p->right);
	}

}

/*
 * main:  a little test program for getword()
 */

int main(void)  {

	struct tnode *root = NULL;
	char   word[MAXWORDSIZE] = "";

	while (getword(word, MAXWORDSIZE) != EOF)
		if (isalpha(word[0]))
			root = treeadd(root, word);

	treeprint(root);

	exit(EXIT_SUCCESS);
}
