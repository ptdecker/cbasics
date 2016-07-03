/*
* wordxrefstem(): cross-reference all words in a document listing the line number upon which each occurs.  When
*      preparing the cross-reference, this version of wordxref uses Martin Porter's stemming algorithm.  This has
*      the effect of consolidating words that are synonyms before building the cross-reference.
*
* c.f. http://tartarus.org/~martin/PorterStemmer/
*      https://en.wikipedia.org/wiki/Stemming
*/

//TODO: Fix splint overrides
//TODO: Refactor stemmer including dropping globals

/*@ -nullderef -branchstate -usedef -exportlocal */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions

#define MAXSTACK    10    // Maximum characters parser can undo
#define MAXWORDSIZE 50    // Maximum number of characters in a word
#define BUFFERSIZE  1024  // Size of word buffer for stemmer
#define RIGHTMARGIN 50    // Position of right-hand margin we will try to maintain

// Globals

static char   buffer[MAXSTACK];   // Array-based buffer of char-typed values
static size_t bufferptr = 0;      // Buffer pointer--next free stack position

// The following are used by the stemmer which should be refactored to avoid such globals //

static char   *b;   // buffer for word to be stemmed
static size_t  k;   // offset to last character in the buffer of the word to be stemmed
static size_t  k0;  // offset to first character in the buffer of the word to be stemmed
static size_t  j;   // j is a general offset into the string

// Structures

// Singlely linked list of line numbers
struct linklist {
	int linenum;           // Line number
	struct linklist *next; // Next item in linked list
};

// Singlely linked list of words
struct linkwords {
	char *word;              // Unstemmed word
	struct linkwords *next;  // Next item in the linked word list
};

// Tree node structure
struct tnode {
	char *word;               // Points to the stemmed word upon which we use to xreference
	int wordcount;            // Number of words in the unstemmed word list
	struct linkwords *words;  // First entry in a linked list of unstemmed words
	struct linklist  *lines;  // First entry in a linked list of line numbers
	struct tnode     *left;   // Left child
	struct tnode     *right;  // Right child
};

/************** START OF MARTIN PORTER'S STEMMER CODE **************/

/* The code below is, pretty much, a straight port of the canonical example Martin Porter
 * provides on his web site (the non-thread safe version).  However, I have updated it to
 * with minor updates for coding styling, better usage of types (bool, size_t, char),
 * comment expansion, partial splint compliance, uage of a big static buffer, etc.
 *
 * NOTE: ends() uses a different approach of stuffing the first byte of the passed string
 *       with the length of the string. I guess Porter does this to keep with his approach
 *       of not leveraging zero-terminated C strings and avoiding the need to count length.
 */

/*
 * cons(): returns 'true' if b[i] is a consonant
 */

static bool cons(size_t i) {
    switch (b[i]) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return false;
        case 'y':
            // Handle the case where 'y' could be a vowel, i.e. it is either
            // the first character of the word to be stemmed or if the prior
            // character in the word is a vowel.
            return (i == k0) ? true : !cons(i - 1);
        default:
            return true;
    }
}

/* m() measures the number of consonant sequences between k0 and j. if c is
   a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
   presence,

      <c><v>       gives 0
      <c>vc<v>     gives 1
      <c>vcvc<v>   gives 2
      <c>vcvcvc<v> gives 3
      ....
*/

static size_t m() {

    size_t n = 0;
    size_t i = k0;

    while (true) {
        if (i > j)
            return n;
        if (! cons(i))
            break;
        i++;
    }
    i++;

    while (true) {
        while (true) {
            if (i > j)
                return n;
            if (cons(i))
                break;
            i++;
        }
        i++;

        n++;
        while (true) {
            if (i > j)
                return n;
            if (! cons(i))
                break;
            i++;
        }
        i++;
    }
}

/* vowelinstem() is TRUE <=> k0,...j contains a vowel */

static bool vowelinstem() {

    size_t i;

    for (i = k0; i <= j; i++)
        if (! cons(i))
            return true;
  
    return false;
}

/* doublec(j) is TRUE <=> j,(j-1) contain a double consonant. */

static bool doublec(size_t j) {

    if (j < k0+1)
        return false;

    if (b[j] != b[j-1])
        return false;

    return cons(j);
}

/* cvc(i) is TRUE <=> i-2,i-1,i has the form consonant - vowel - consonant
   and also if the second c is not w,x or y. this is used when trying to
   restore an e at the end of a short word. e.g.

      cav(e), lov(e), hop(e), crim(e), but
      snow, box, tray.

*/

static bool cvc(size_t i) {

    int ch;

    if (i < k0 + 2 || !cons(i) || cons(i - 1) || !cons(i - 2))
        return false;

    ch = b[i];
    if (ch == 'w' || ch == 'x' || ch == 'y')
        return false;
   
    return true;
}

/* ends(s) is TRUE <=> k0,...k ends with the string s. */

static bool ends(char *s) {

    size_t length = (size_t)s[0];

    if (s[length] != b[k])
        return false; /* tiny speed-up */

    if (length > k - k0 + 1)
        return false;

    if (memcmp(b + k - length + 1, s + 1, length) != 0)
        return false;

    // Below differs from Martin Porter's code in that he was using ints which can
    // go negative and he allows 'j' to do so here in some cases.  Switching to 
    // unsigned 'size_t' type (for array indexes) breaks when the negative attempt
    // is made resulting in a segmentation fault occuring inside 'm()'.  The hack
    // below forces 'j' to zero in this case and addresses the issue.
    j = (length > k) ? 0 : (k - length);

    return true;
}

/* setto(s) sets (j+1),...k to the characters in the string s, readjusting
   k. */

static void setto(char *s) {

    size_t length = (size_t)s[0];

    memmove(b + j + 1, s + 1, length);

    k = j + length;
}

/* r(s) is used further down. */

static void r(char *s) {

    if (m() > 0)
        setto(s);
}

/* step1ab() gets rid of plurals and -ed or -ing. e.g.

       caresses  ->  caress
       ponies    ->  poni
       ties      ->  ti
       caress    ->  caress
       cats      ->  cat

       feed      ->  feed
       agreed    ->  agree
       disabled  ->  disable

       matting   ->  mat
       mating    ->  mate
       meeting   ->  meet
       milling   ->  mill
       messing   ->  mess

       meetings  ->  meet

*/

static void step1ab() {

    char ch;

    if (b[k] == 's') {
        if (ends("\04" "sses"))
            k -= 2;
        else if (ends("\03" "ies"))
            setto("\01" "i");
        else if (b[k-1] != 's')
            k--;
    }

    if (ends("\03" "eed")) {
        if (m() > 0)
            k--;
    } else if ((ends("\02" "ed") || ends("\03" "ing") || ends("\02" "in")) && vowelinstem()) {
        k = j;
        if (ends("\02" "at"))
            setto("\03" "ate");
        else if (ends("\02" "bl"))
            setto("\03" "ble");
        else if (ends("\02" "iz"))
            setto("\03" "ize");
        else if (doublec(k)) {
            k--;
            ch = b[k];
            if (ch == 'l' || ch == 's' || ch == 'z')
                k++;
        } else if (m() == 1 && cvc(k))
            setto("\01" "e");
    }
}

/* step1c() turns terminal y to i when there is another vowel in the stem. */

static void step1c() {

//    fprintf(stderr, "1c");

    if (ends("\01" "y") && vowelinstem())
        b[k] = 'i';
}


/* step2() maps double suffices to single ones. so -ization ( = -ize plus
   -ation) maps to -ize etc. note that the string before the suffix must give
   m() > 0. */

static void step2() {

    switch (b[k - 1]) {

        case 'a':
            if (ends("\07" "ational")) {
            	r("\03" "ate");
                break;
            }
            if (ends("\06" "tional")) {
                r("\04" "tion");
                break;
            }
            break;

        case 'c':
            if (ends("\04" "enci")) {
                r("\04" "ence");
                break;
            }
            if (ends("\04" "anci")) {
                r("\04" "ance");
                break;
            }
            break;

        case 'e':
            if (ends("\04" "izer")) {
                r("\03" "ize");
                break;
            }
            break;

        case 'l':
            if (ends("\03" "bli")) {
                r("\03" "ble");
                break;
            }

// DEPARTURE: To match the published algorithm, replace the above if clause with
//          if (ends("\04" "abli")) {
//              r("\04" "able");
//              break;
//           }

            if (ends("\04" "alli")) {
                r("\02" "al");
                break;
            }
            if (ends("\05" "entli")) {
                r("\03" "ent");
                break;
            }
            if (ends("\03" "eli")) {
                r("\01" "e");
                break;
            }
            if (ends("\05" "ousli")) {
                r("\03" "ous");
                break;
            }
            break;

        case 'o':
            if (ends("\07" "ization")) {
                r("\03" "ize");
                break;
            }
            if (ends("\05" "ation")) {
                r("\03" "ate");
                break;
            }
            if (ends("\04" "ator")) {
                r("\03" "ate");
                break;
            }
            break;

        case 's':
            if (ends("\05" "alism")) {
                r("\02" "al");
                break;
            }
            if (ends("\07" "iveness")) {
                r("\03" "ive");
                break;
            }
            if (ends("\07" "fulness")) {
                r("\03" "ful");
                break;
            }
            if (ends("\07" "ousness")) {
                r("\03" "ous");
                break;
            }
            break;

        case 't':
            if (ends("\05" "aliti")) {
                r("\02" "al");
                break;
            }
            if (ends("\05" "iviti")) {
                r("\03" "ive");
                break;
            }
            if (ends("\06" "biliti")) {
                r("\03" "ble");
                break;
            }
            break;

// DEPARTURE: To match the published algorithm, delete this next case statement

        case 'g':
            if (ends("\04" "logi")) {
               r("\03" "log");
               break;
            }

    }
}

/* step3() deals with -ic-, -full, -ness etc. similar strategy to step2. */

static void step3() {

    switch (b[k]) {

        case 'e':
            if (ends("\05" "icate")) {
                r("\02" "ic");
                break;
            }
            if (ends("\05" "ative")) {
                r("\00" "");
                break;
            }
            if (ends("\05" "alize")) {
                r("\02" "al");
                break;
            }
            break;

        case 'i':
            if (ends("\05" "iciti")) {
                r("\02" "ic");
                break;
            }
            break;

        case 'l':
            if (ends("\04" "ical")) {
                r("\02" "ic");
                break;
            }
            if (ends("\03" "ful")) {
                r("\00" "");
                break;
            }
            break;

        case 's':
            if (ends("\04" "ness")) {
                r("\00" "");
                break;
            }
            break;
    }
}

/* step4() takes off -ant, -ence etc., in context <c>vcvc<v>. */

static void step4() {

    switch (b[k-1]) {

        case 'a':
            if (ends("\02" "al"))
                break;
            return;

        case 'c':
            if (ends("\04" "ance"))
                break;
            if (ends("\04" "ence"))
                break;
            return;

        case 'e':
            if (ends("\02" "er"))
                break;
            return;

        case 'i':
            if (ends("\02" "ic"))
                break;
            return;

        case 'l':
            if (ends("\04" "able"))
                break;
            if (ends("\04" "ible"))
                break;
            return;

        case 'n':
            if (ends("\03" "ant"))
                break;
            if (ends("\05" "ement"))
                break;
            if (ends("\04" "ment"))
                break;
            if (ends("\03" "ent"))
                break;
            return;

        case 'o':
            if (ends("\03" "ion") && j >= k0 && (b[j] == 's' || b[j] == 't'))
                break;
            if (ends("\02" "ou")) // Takes care of -ous
                break;
            return;

        case 's':
            if (ends("\03" "ism"))
                break;
            return;

        case 't':
            if (ends("\03" "ate"))
                break;
            if (ends("\03" "iti"))
                break;
            return;

        case 'u':
            if (ends("\03" "ous"))
                break;
            return;

        case 'v':
            if (ends("\03" "ive"))
                break;
            return;

        case 'z':
            if (ends("\03" "ize"))
                break;
            return;

        default:
            return;
    }

    if (m() > 1)
        k = j;
}

/* step5() removes a final -e if m() > 1, and changes -ll to -l if
   m() > 1. */

static void step5() {

    size_t a;

    j = k;

    if (b[k] == 'e') {
      a = m();
      if (a > 1 || (a == 1 && !cvc(k - 1)))
          k--;
    }

    if (b[k] == 'l' && doublec(k) && m() > 1)
      k--;
}

/* In stem(p,i,j), p is a char pointer, and the string to be stemmed is from
   p[i] to p[j] inclusive. Typically i is zero and j is the offset to the last
   character of a string, (p[j+1] == '\0'). The stemmer adjusts the
   characters p[i] ... p[j] and returns the new end-point of the string, k.
   Stemming never increases word length, so i <= k <= j. To turn the stemmer
   into a module, declare 'stem' as extern, and delete the remainder of this
   file.
*/

static size_t stem(char *p, size_t i, size_t j) {

    b  = p;
    k  = j;
    k0 = i; /* copy the parameters into statics */

    /*
     * DEPARTURE: This next 'if' statement prevents strings of length 1 or 2 from
     * going through the stemming process, although no mention is made of this in the
     * published algorithm. Remove the line to match the publishedalgorithm.
     */

    if (k <= k0 + 1)
        return k;

    step1ab();
    if (k > k0) {
        step1c();
        step2();
        step3();
        step4();
        step5();
    }

    return k;
}

/************** END OF MARTIN PORTER'S STEMMER CODE **************/

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

	struct linklist *temp = p->lines;

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
 * lalloc():  make a new linked word node
 */

static struct linkwords *lwalloc(void) {

	struct linkwords *p = (struct linkwords *)malloc(sizeof(struct linkwords));
	if (p == NULL) {
		printf("Error: ran out of memory");
		exit(EXIT_FAILURE);
	}

	return p;
}

/*
 * addword(): adds a word to a linked list of unstemmed words stored in a tnode
 */

static void addword(struct tnode *p, char *uw) {

	struct linkwords *temp = p->words;

	// Walk down the linked list looking for the end or the word
	while (temp->next != NULL && strcmp(temp->word, uw) != 0)
		temp = temp->next;

	// If we found the end then add the word to the list
	if (strcmp(temp->word, uw) != 0) {
		temp->next = lwalloc();
		temp->next->word = mystrdup(uw);
		temp->next->next = NULL;
		p->wordcount++;
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
 * treeadd(): add a node to our tree
 */

static struct tnode *treeadd(struct tnode *p, char *w, char *uw, int line) {

	int cond;

	if (p == NULL) {
		// Create new tnode
		p = talloc();
		p->word  = mystrdup(w);
		p->words = lwalloc();
		p->words->word = mystrdup(uw);
		p->words->next = NULL;
		p->wordcount = 1;
		p->lines = lalloc();
		p->lines->linenum = line;
		p->lines->next = NULL;
		p->right = NULL;
		p->left  = NULL;
	} else if ((cond = strncmp(w, p->word, MAXWORDSIZE)) == 0) {
		// Update existing tnode
		addword(p, uw);
		addline(p, line);
	} else if (cond < 0)
		// Traverse left-hand side of tree
		p->left  = treeadd(p->left, w, uw, line);
	else
		// Traverse right-hand side of tree
		p->right = treeadd(p->right, w, uw, line);

	return p;
}

/*
 * listsort(): sort (basic bubble sort) the linked list of words
 */

static void listsort(struct linkwords *head, int num_nodes) {

    struct linkwords *current;
    struct linkwords *next;
    struct linkwords *previous;
	int i;

    for (i = 0; i < num_nodes; i++) {

        current = head;
        next = current->next;
        previous = NULL;

        while(next != NULL) {

            if (strcmp(current->word, next->word) > 0) {
                if (current == head)
                    head = next;
                else
                    previous->next = next;
                current->next = next->next;
                next->next = current; 
                previous = next;
                next = current->next;
            } else { 
                previous = current;
                current = current->next;
                next = current->next;
            }
        }
    }
}

/*
 * treeprint: traverse the tree in order and print node if p->match is true
 */

static void treeprint(struct tnode *p) {

	struct linkwords *temp1;
	struct linklist  *temp2;

	int pos;

	if (p != NULL) {

		// Traverse left side of tree
		treeprint(p->left);

		// Sort the unstemmed words on the current node
		listsort(p->words, p->wordcount);

		// Print out the words
		for (temp1 = p->words; temp1 != NULL; temp1 = temp1->next) {
			printf("%s", temp1->word);
			if (temp1->next != NULL)
				printf(", ");
		}
		(void)putchar('\n');

		// Print out the line numbers adjusting for rough right margin
		pos = printf("\t");
		for (temp2 = p->lines; temp2 != NULL; temp2 = temp2->next) {
			pos += printf("%d", temp2->linenum);
			if (temp2->next != NULL)
				pos += printf(", ");
			if (pos > RIGHTMARGIN && temp2->next != NULL) {
				(void)putchar('\n');
				pos = printf("\t");
			}
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
 * squeezechar(): Deletes all 'c' from S[]
 *
 * NOTE: squeezechar() is the version of squeeze() implemnted in 2.8 of K&R
 *       and squeeze() is ther alternate version suggested by the excercises.
 */

static void squeezechar(char *s, char c) {

    char *squeezed = s;

    for ( ; *s != '\0'; s++)
        if (*s != c)
            *squeezed++ = *s;

    *squeezed = '\0';
}

/*
 * main
 */

int main(void)  {

	struct tnode *root            = NULL;
	char   word[MAXWORDSIZE]      = "";
	char   unstemmed[MAXWORDSIZE] = "";
	int    line                   = 1;

	while (getword(word, MAXWORDSIZE) != EOF)
		if (isalpha(word[0])) {
			lowerstr(word);
			if (isnotstopword(word)) {
				strncpy(unstemmed, word, MAXWORDSIZE);
				squeezechar(word, '\'');
				word[stem(word, 0, strlen(word) - 1) + 1] = '\0'; 
				root = treeadd(root, word, unstemmed, line);
			}
		} else if (word[0] == '\n')
			line++;

	treeprint(root);

	exit(EXIT_SUCCESS);
}
