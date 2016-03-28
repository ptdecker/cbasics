/*
 * Perform rudimentary syntax checks on a C program
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Comment states

#define NOCOMM 0  // Current character is not within a comment
#define BLOCK  1  // Current character is within a block comment
#define LINE   2  // Current character is within a line comment

// Globals to track prior, current, and next characters
// read from the input stream

static char prior = '\0';
static char current;
static char next;

/*
 * eatchar()
 * Helper function to eat a character from the stream
 */

static void eatchar(void) {
    prior = current;
    current = next;
    next = getchar();
}

/* Main */

int main(void) {

    int  commtype = NOCOMM;  // Comment state
    bool indquote = false;   // Inside a double quoted string state
    bool insquote = false;   // Inside a single quoted string state

    int brace  = 0; // number of unclosed bracers
    int paren  = 0; // number of unclosed parenthesis
    int brack  = 0; // number of unclosed brackets
    int dquote = 0; // number of double quotes
    int squote = 0; // number of single quotes

    current = getchar();
    while (current != EOF) {

        // Get look-ahead character

        next = getchar();

        // Perform lexical evaluation to determine state

        if (current == '\"' && prior != '\\' && next != '\'')
            // handle double quoted text string start & stop
            if (indquote) {
                indquote = false;
                dquote--;
            } else {
                indquote = true;
                dquote++;
            }
        else if (!indquote && current == '\'' && prior != '\\')
            // handle single quoted text
            if (insquote) {
                insquote = false;
                squote--;
            } else {
                insquote = true;
                squote++;
            }
        else if (!indquote && current == '/' && next == '*') {
            // handle the start of a block comment
            eatchar();
            commtype = BLOCK;
        } else if (!indquote && current == '/' && next == '/') {
            // handle the start of a line comment
            eatchar();
            commtype = LINE;
        } else if (!indquote && current == '*' && next == '/') {
            // handle the end of either a block or line comment
            eatchar();
            commtype = NOCOMM;
        } else if (commtype == NOCOMM || (commtype == LINE && current == '\n')) {
            commtype = NOCOMM;
            if (!indquote && !insquote && current == '(')
                paren++;
            else if (!indquote && !insquote  && current == ')')
                paren--;
            else if (!indquote && !insquote  && current == '[')
                brack++;
            else if (!indquote && !insquote  && current == ']')
                brack--;
            else if (!indquote && !insquote  && current == '{')
                brace++;
            else if (!indquote && !insquote  && current == '}')
                brace--;
        }

        // Check for errors

        if (paren < 0) {
            printf("Too many closed parenthesis\n");
            paren = 0;
        } else if (brack < 0) {
            printf("Too many closed brackets\n");
            brack = 0;
        } else if (brace < 0) {
            printf("Too many closed bracers\n");
            brace = 0;
        }

        // Preserve current character as prior and move look-ahead to current

        prior = current;
        current = next;
    }

    // Check for final errors

    if (paren > 0)
        printf("Too many open parenthesis\n");
    if (brack > 0)
        printf("Too many open brackets\n");
    if (brace > 0)
        printf("Too many open bracers\n");
    if (dquote != 0)
        printf("Unmatached double quotes\n");
    if (squote != 0)
        printf("Unmatched single quotes\n");

    exit(EXIT_SUCCESS);
}
