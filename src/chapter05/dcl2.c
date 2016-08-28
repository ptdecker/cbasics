/*
 *  dcl(): parses a C-style declartion
 */

// Includes

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions

#define MAXOUTSTR 1000  // Maximum output string
#define MAXSTACK    10  // Maximum characters parser can undo
#define MAXTOKEN   100  // Maximum token size

// Enumerations

enum { NAME, PARENS, BRACKETS };

// Globals

static int    tokentype;          // Type of last token
static char   token[MAXTOKEN];    // Last token string
static char   name[MAXTOKEN];     // Identifier name
static char   datatype[MAXTOKEN]; // Data type ('char', 'int', etc)
static char   out[MAXOUTSTR];     // Output string
static char   buffer[MAXSTACK];   // Array-based buffer of char-typed values
static size_t bufferptr = 0;      // Buffer pointer--next free stack position
static bool   prevtoken = false;  // Indicates if there is a previous token

// Forward declarations

static void dcl(void);

/*
 * errmsg(): prints an error message
 */

static void errmsg(char *msg) {
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

static int gettoken(void) {

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
 * scompare(): compares to strings (used by bsearch in notstopword)
 */

static int scompare(char **s, char **t) {
    return strcmp(*s, *t);
}

/*
 * typequal(): returns true if a token is a type-qualifier
 *
 * NOTE: since we are using bsearch to search typeq[], typeq[]'s' values must be in ascending order
 */

static bool typequal(void) {

    static char *typeq[] = {
        "const",
        "volatile"
    };
    char *pt = token;

    char **result;

    result = (char **)bsearch( (char *) &pt, (char *)typeq, sizeof(typeq)/sizeof(typeq[0]),
                              sizeof( char * ), (int (*)(const void*, const void*))scompare);

    return (result != NULL);
}

/*
 * typespec(): returns true if a token is a type-specifier
 *
 * NOTE: since we are using bsearch to search types[], types[]'s' values must be in ascending order
 */

static bool typespec(void) {

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

    char **result;

    result = (char **)bsearch( (char *) &pt, (char *)types, sizeof(types)/sizeof(types[0]),
                              sizeof( char * ), (int (*)(const void*, const void*))scompare);

    return (result != NULL);}

/*
 * dclspec(): interpret a declaration specification
 */

static void dclspec(void) {

    char temp[MAXTOKEN];


    temp[0] = '\0';
    (void)gettoken();
    do {
        if (tokentype != NAME) {
            prevtoken = true;
            dcl();
        } else if (typespec() || typequal()) {
            strcat(temp, " ");
            strcat(temp, token);
            (void)gettoken();
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

static void parmdcl(void) {
    do {
        dclspec();
    } while (tokentype == ',');
    if (tokentype != ')')
        errmsg("missing ')' in parameter declaration\n");
}

/*
 * dirdcl(): parse a direct declarator
 */

static void dirdcl(void) {

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

static void dcl(void) {

    int ns; // number of asterisks

    for (ns = 0; gettoken() == '*'; )
        ns++;

    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* Main */

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

    return 0;
}
