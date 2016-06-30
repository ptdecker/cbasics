/*
* wordxref(): cross-reference all words in a document listing the line number upon which each occurs
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

struct linklist {
	int linenum;           // Line number
	struct linklist *next; // Next item in linked list
};

struct tnode {
	char *word;              // Points to the text stored in the node
	struct linklist *lines;  // First entry in a linked list of line numbers
	struct tnode    *left;   // Left child
	struct tnode    *right;  // Right child
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
	while (isspace(c = getch()) && c != '\n')
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
 * compare()  compare words and update p->match
 */

static int compare(char *s, struct tnode *p) {
	return strncmp(s, p->word, MAXWORDSIZE);
}

/*
 * lalloc():  make a new linked list node
 */

static struct linklist *lalloc(void) {

	struct linklist *p = (struct linklist *)malloc(sizeof(struct linklist));

	if (p == NULL) {
		printf("Error: ran out of memory");
		exit(EXIT_FAILURE);
	}

	return p;
}

/*
 * addline(): adds a line number to a linked list of line numbers stored in a tnode
 */

static void addline(struct tnode *p, int linenum) {

	struct linklist *temp;

	temp = p->lines;

	// Walk down the linked list looking for the end or the line number
	while (temp->next != NULL && temp->linenum != linenum)
		temp = temp->next;

	// If we found the end then add the line number to the list
	if (temp->linenum != linenum) {
		temp->next = lalloc();
		temp->next->linenum = linenum;
		temp->next->next = NULL;
	}

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

static struct tnode *treeadd(struct tnode *p, char *w, int line) {

	int cond;

	if (p == NULL) {
		p = talloc();
		p->word  = mystrdup(w);
		p->lines = lalloc();
		p->lines->linenum = line;
		p->lines->next = NULL;
		p->right = NULL;
		p->left  = NULL;
	} else if ((cond = compare(w, p)) == 0)
		addline(p, line);
	else if (cond < 0)
		p->left  = treeadd(p->left, w, line);
	else
		p->right = treeadd(p->right, w, line);

	return p;
}

/*
 * treeprint: traverse the tree in order and print node if p->match is true
 */

static void treeprint(struct tnode *p) {

	struct linklist *temp;

	if (p != NULL) {
		treeprint(p->left);
		printf("%s\n", p->word);
		(void)putchar('\t');
		for (temp = p->lines; temp != NULL; temp = temp->next) {
			printf("%d", temp->linenum);
			if (temp->next != NULL)
				printf(", ");
		}
		(void)putchar('\n');
		treeprint(p->right);
	}

}

/*
 * lowerstr(): Converts a string to lower case
 */

static void lowerstr(char *s) {
	for ( ; *s != '\0'; s++)
		*s = tolower(*s);
}

/*
 * scompare(): compares to strings (used by bsearch in notstopword)
 */

static int scompare(char **s, char **t) {
	return strcmp(*s, *t);
}

/*
 * isnotstopword(): returns true if a word is not a stop word
 *
 * Note:  Here are sources of the stop words lists from which the list below was formed:
 *             - http://www.ranks.nl/stopwords/
 *             - http://xpo6.com/list-of-english-stop-words/
 */

static bool isnotstopword(char *w) {

	static char *stopwords[] = {
		"a","about","above","after","again","against","all","am","an","and","any","are","aren't","as","at","be",
		"because","been","before","being","below","between","both","but","by","can't","cannot","could","couldn't",
		"did","didn't","do","does","doesn't","doing","don't","down","during","each","few","for","from","further",
		"had","hadn't","has","hasn't","have","haven't","having","he","he'd","he'll","he's","her","here","here's",
		"hers","herself","him","himself","his","how","how's","i","i'd","i'll","i'm","i've","if","in","into","is",
		"isn't","it","it's","its","itself","let's","me","more","most","mustn't","my","myself","no","nor","not","of",
		"off","on","once","only","or","other","ought","our","ours","ourselves","out","over","own","same","shan't",
		"she","she'd","she'll","she's","should","shouldn't","so","some","such","than","that","that's","the","their",
		"theirs","them","themselves","then","there","there's","these","they","they'd","they'll","they're","they've",
		"this","those","through","to","too","under","until","up","very","was","wasn't","we","we'd","we'll","we're",
		"we've","were","weren't","what","what's","when","when's","where","where's","which","while","who","who's",
		"whom","why","why's","with","won't","would","wouldn't","you","you'd","you'll","you're","you've","your",
		"yours","yourself","yourselves"
	};
	char **result;

	result = (char **)bsearch( (char *) &w, (char *)stopwords, sizeof(stopwords)/sizeof(stopwords[0]),
                              sizeof( char * ), (int (*)(const void*, const void*))scompare);

	return result == NULL;
}

/*
 * main:  a little test program for getword()
 */

int main(void)  {

	struct tnode *root = NULL;
	char   word[MAXWORDSIZE] = "";
	int    line = 1;

	while (getword(word, MAXWORDSIZE) != EOF)
		if (isalpha(word[0])) {
			lowerstr(word);
			if (isnotstopword(word))
				root = treeadd(root, word, line);
		} else if (word[0] == '\n')
			line++;

	treeprint(root);

	exit(EXIT_SUCCESS);
}
