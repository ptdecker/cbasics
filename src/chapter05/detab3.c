/*
 * Replaces tabs with spaces
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
 * detab(): copy stdin to stdout replacing all tab characters ('\t') with spaces (' ') according
 *          to a set of tab stops
 */

static void detab(char *tabstop) {

    char c;
    int  pos = 1;

    while ((c = getchar()) != EOF)
        if (c == '\t')
            do
                (void)putchar(' ');
            while (isnottab(pos++, tabstop));
        else {
            (void)putchar(c);
            pos = (c == '\n') ? 1 : ++pos;
        }
}

/*
 * Main
 */

int main(int argc, char *argv[]) {

    char tabstop[MAXLINE + 1];

    settabs(argc, argv, tabstop);
    detab(tabstop);

    exit(EXIT_SUCCESS);
}
