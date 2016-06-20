/*
 * Replaces tabs with spaces up to set tab stops
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define TABSTOPINC 4    // Default tab size
#define MAXLINE    250  // Maximum supported line length

/*
 * isnottab(): returns true if the tab position 'pos' is not a tab stop
 */

static bool isnottab(int pos, char *tabstop) {
    return (pos < (MAXLINE + 1)) && (tabstop[pos] == false);
}

/*
 * settabs(): sets tab stops
 */

static void settabs(int argc, char *argv[], char *tabstop) {

    int i;

    // If no tabs were passed as arguments, set default tab stops and
    // return to caller

    if (argc < 2) {
        for (i = 1; i <= MAXLINE; i++)
            tabstop[i] = ((i % TABSTOPINC) == 0);
        return;
    }

    // Clear tab stops

    for (i = 1; i <= MAXLINE; i++)
        tabstop[i] = false;

    // If the first argument starts with '-' and the second with '+', assume that the user
    // provided a range

    if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {
        int next   = atoi(&(*++argv[1])); // where to start setting tab stops
        int repeat = atoi(&(*++argv[2])); // number of columns to repeat tab stops
        for (i = next; i <= MAXLINE; i += repeat)
            tabstop[i] = true;
    }

    // Set tabs based upon passed arguments

    while (--argc > 0) {
        i = atoi(*++argv);
        if (0 < i && i <= MAXLINE)
            tabstop[i] = true;
    }

}

/*
 * entab(): copies stdin to stdout replacing runs of spaces (' ') with tab characters ('\t') according to
 *          a set of tab stops
 */

void entab(char *tab) {

    char c;        // Current character
    int  pos = 1;  // Current position within a line
    int  ns  = 0;  // Number of spaces required
    int  nt  = 0;  // Number of tabs required

    for ( ; (c = getchar()) != EOF; pos++) {

        // when the next character is a space ...
        //     if we are at a tab stop then we do not need any spaces and
        //     can use a tab; otherwise, will need a space.  Either way, 
        //     move on to the next character

        if (c == ' ') {
            if (isnottab(pos, tab))
                ++ns;
            else {
                ns = 0;
                ++nt;
            }
            continue;
        }

        // when the next character is not a space ...
        // ... first, output the tabs we need;
        for ( ; nt > 0; nt--)
            (void)putchar('\t');

        // ...second, output the spaces unless next character is a tab
        //     in which case, ignore any accumulated spaces
        for (ns = (c == '\t') ? 0 : ns; ns > 0; ns--)
            (void)putchar(' ');

        // ...then, output our character
        (void)putchar(c);

        // ... finally, after doing so, reset position
        if (c == '\n')
            pos = 0;

        if (c == '\t')
            while (isnottab(pos, tab))
                ++pos;

    }

}

int main(int argc, char *argv[]) {

    char tabstop[MAXLINE + 1];

    settabs(argc, argv, tabstop);
    entab(tabstop);

    exit(EXIT_SUCCESS);
}
