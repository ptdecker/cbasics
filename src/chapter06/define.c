/*
 * define: A simple '#define' pre-processor that leverages hash table based table look-up routines. Only handles
 *         simple substitution defines
 */

/*@ -unqualifiedtrans -nullderef -mustfreefresh -onlytrans -kepttrans -nullret */

// Includes

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions

#define MAXSTACK 10
#define MAXWORD  100
#define HASHSIZE 101

// Structures

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

// Globals

static char   buffer[MAXSTACK];         // Array-based buffer of char-typed values
static size_t bufferptr = 0;            // Buffer pointer--next free stack position
static struct nlist *hashtab[HASHSIZE]; // Pointer table

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
 * peekch(): peek at the next character
 */

static char peekch() {
    char c;
    ungetch(c = getch());
    return c;
}

/*
 * ungets(): ungets a whole string back to the buffer
 */

static void ungets(char s[]) {
    size_t slen = strlen(s);
    while (slen > 0)
        ungetch(s[--slen]);
}

/*
 * error(): print error messages and skip the rest of the line
 */

static void error(int c, char *s) {
    printf("%s\n", s);
    while (c != EOF && c != '\n')
        c = getch();
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
 * comment(): skip over a comment and return a character
 */

static char comment(void) {
    char c;
    while ((c = getch()) != EOF)
        if (c == '*' && peekch() == '/') {
            c = getch();
            c = getch();
            break;
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
    char *w = word;

    // Add character to the word buffer if we are not yet at EOF
    if ((c = getch()) != EOF)
        *w++ = c;

    // Handle text allowing for underscores and pre-processor control lines
    if (isalpha(c) || c == '_') {
        for ( ; --lim > 0; w++)
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }

    } else if (isdigit(c)) {
        for ( ; --lim > 0; w++)
            if (!isdigit(*w = getch()) && *w != '.') {
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
        if (peekch() == '*') {
            c = comment();
            w--;
        } else if (peekch() == '/') {
            while ((c = getch()) != EOF && c != '\n')
                ; // Empty
            w--;
            *w++ = '\n';
        }
    }

    // Terminate our word buffer and return the first character
    *w = '\0';
    return c;
}

/*
 * hash(): Calculates a hash value for a given string
 */

static unsigned hash(char *s) {

    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

/*
 * lookup(): Look for s in the hash table
 */

static struct nlist *lookup(char *s) {

    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  // Found

    return NULL; // Not found
}

/*
 * install(): Put a value into the hash table
 */

static struct nlist *install(char *name, char *defn) {

    struct nlist *np;

    if ((np = lookup(name)) == NULL) {

        // Value not found in hash table so add it

        unsigned hashval;

        if ((np = (struct nlist *)malloc(sizeof(*np))) == NULL) {
            printf("Error: ran out of memory");
            exit(EXIT_FAILURE);
        }
        hashval  = hash(name);
        np->name = mystrdup(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;

    } else

        // Value found so free up the previous value (to be replaced with the new)

        free((void *)np->defn);

    np->defn = mystrdup(defn);

    return np;
}

/*
 * undef(): remove a name and definition from the table
 */

static void undef(char *s) {

    unsigned h;
    struct nlist *prior;
    struct nlist *np;

    prior = NULL;
    h = hash(s);

    for (np = hashtab[h]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0)
            break;
        prior = np;
    }

    if (np != NULL) {
        if (prior == NULL)
            hashtab[h] = np->next;
        else
            prior->next = np->next;

        free((void *)np->name);
        free((void *)np->defn);
        free((void *)np);
    }

}

/*
 * skipblanks(): skip blank and tab characters
 */

static void skipblanks(void) {

    int c;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    ungetch(c);
}

/*
 * getdef: get definition and install it
 */

static void getdef(void) {

    char def[MAXWORD]  = "";
    char dir[MAXWORD]  = "";
    char name[MAXWORD] = "";
    int  i;

    skipblanks();

    if (!isalpha(getword(dir, MAXWORD)))
        error(dir[0], "getdef: expecting a directive after '#'--got '%s'");
    else if (strcmp(dir, "define") == 0) {
        skipblanks();
        if (!isalpha(getword(name, MAXWORD)))
            error(name[0], "getdef: non-alpha name expected");
        else {
            skipblanks();
            for (i = 0; i < MAXWORD - 1; i++)
                if ((def[i] = getch()) == EOF || def[i] == '\n')
                    break;
            def[i] = '\0';
            if (i <= 0)
                error('\n', "getdef; incomplete define");
            else
                (void)install(name, def);
        }
    } else if (strcmp(dir, "undef") == 0) {
        skipblanks();
        if (!isalpha(getword(name, MAXWORD)))
            error(name[0], "getdef: non-alpha in undef");
        else
            undef(name);
    } else if (strcmp(dir, "include") == 0) {
        // Here is where includes should be handled
        printf("#include");
    } else
        error(dir[0], "getdef: expecting a directive after #");

}

/*
 * Main
 */

int main(void) {

    char w[MAXWORD] = "";
    struct nlist *np;

    while (getword(w, MAXWORD) != EOF)
        if (w[0] == '#')
            getdef();
        else if (!isalpha(w[0]))
            printf("%s", w);
        else if ((np = lookup(w)) == NULL)
            printf("%s", w);
        else
            ungets(np->defn);

    return 0;
}
