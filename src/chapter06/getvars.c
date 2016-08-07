/*
* getvars(): gets the variables from a C program
*/


#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitinos

#define MAXSTACK      10    // Maximum characters parser can undo
#define MAXWORDSIZE   50    // Maximum number of characters in a word
#define KEY_NOT_FOUND EOF
#define NOTFOUND      -1

// Globals

static char   buffer[MAXSTACK];   // Array-based buffer of char-typed values
static size_t bufferptr = 0;      // Buffer pointer--next free stack position

static struct key {
 	char *word;
 	int   count;
 } keytab[] = {
 	{"auto",     0 },
 	{"bool",     0 },
 	{"break",    0 },
 	{"case",     0 },
 	{"char",     0 },
 	{"const",    0 },
 	{"continue", 0 },
 	{"default",  0 },
 	{"do",       0 },
 	{"double",   0 },
 	{"else",     0 },
 	{"enum",     0 },
 	{"extern",   0 },
 	{"false",    0 },
 	{"float",    0 },
 	{"for",      0 },
 	{"goto",     0 },
 	{"if",       0 },
 	{"int",      0 },
 	{"long",     0 },
 	{"register", 0 },
 	{"return",   0 },
 	{"short",    0 },
 	{"signed",   0 },
 	{"sizeof",   0 },
 	{"static",   0 },
 	{"struct",   0 },
 	{"switch",   0 },
 	{"true",     0 },
 	{"typedef",  0 },
 	{"union",    0 },
 	{"unsigned", 0 },
 	{"void",     0 },
 	{"volatile", 0 },
 	{"while",    0 },
 };

static const size_t numkeys = (size_t)(sizeof keytab / sizeof(struct key));

// Structures

struct tnode {
	char *word;          // Points to the text stored in the node
	bool match;          // Indicates if a match was found
	struct tnode *left;  // Left child
	struct tnode *right; // Right child
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
 * comment(): skip over a comment and return a character
 */

static char comment(void) {
	char c;
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

	// Handle text allowing for underscores and pre-processor control lines.
	// Also, handle ignoring function names
	if (isalpha(c) || c == '_' || c == '#')
		for ( ; --lim > 0; w++) {
			if (!isalnum(*w = getch()) && *w != '_' && *w != '.') {
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
 * compare()  compare words and update p->match
 */

static int compare(char *s, struct tnode *p, int num, bool *found) {

	int i;
	char *t = p->word;

	// If all characters in the two strings match, return zero; otherwise,
	// exit loop with 'i' indicating how many characters we looked at before
	// finding a difference
	for (i = 0; *s == *t; i++, s++, t++)
		if (*s == '\0')
			return 0;

	// If the number of matching characters is greater or equal to the 
	// number we're looking for then update the found indicator
	if (i >= num) {
		*found = true;
		p->match = true;
	}

	return *s - *t;
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
 * addtree(): add a node to our tree
 */

static struct tnode *treeadd(struct tnode *p, char *w, int num, bool *found) {

	int cond;

	if (p == NULL) {
		p = talloc();
		p->word  = mystrdup(w);
		p->match = *found;
		p->right = NULL;
		p->left  = NULL;
	} else if ((cond = compare(w, p, num, found)) < 0)
		p->left  = treeadd(p->left, w, num, found);
	else if (cond > 0)
		p->right = treeadd(p->right, w, num, found);

	return p;
}

/*
 * treeprint: traverse the tree in order and print node if p->match is true
 */

static void treeprint(struct tnode *p) {

	if (p != NULL) {
		treeprint(p->left);
		if (p->match)
			printf("%s\n", p->word);
		treeprint(p->right);
	}

}

/*
 * binsearch(): find word in tab[0]...tab[n-1]
 */

static struct key *binsearch(char *word, struct key tab[], size_t n) {

	struct key *low  = &tab[0];
	struct key *high = &tab[n];
	int    cond = 0;

	while (low < high) {
		struct key *mid = low + (high - low) / 2;
		cond = strcmp(word, mid->word);
		if (cond < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;

	}

	return NULL;
};

/*
 * any(): Returns the first location in string s[] where the character c occurs.
 *        Returns -1 if no characters in c[] are found within s[]
 */

static int anychar(char *s, char c) {
    char *sindex = s;
    while (*sindex != '\0') {
        if (*sindex++ == c)
            return (int)(sindex - s - 1);
    }
    return NOTFOUND;
}

/*
 * main:  a little test program for getword()
 */

int main(int argc, char *argv[])  {

	struct tnode *root = NULL;
	int           num = (--argc == 1 && *(++argv)[0] == '-') ? atoi(argv[0] + 1) : 6;
	char          word[MAXWORDSIZE] = "";
	bool          found = false;
	char          c;

	while (getword(word, MAXWORDSIZE) != EOF) {
		if ((c = getch()) == '(')
			continue;
		ungetch(c); 
		if (isalpha(word[0]) && (int)strlen(word) >= num && binsearch(word, keytab, numkeys) == NULL && anychar(word, '.') == NOTFOUND)
			root = treeadd(root, word, num, &found);
		found = false;
	}

	treeprint(root);

	return 0;
}
