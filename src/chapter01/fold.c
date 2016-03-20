/*
 * Fold text lines to a specific width
 *
 * NOTE: This solution comes almost directly from _The C Answer Book_
 *       by Clovis Tondo & Scott Gimplel.  I'm sorry to say, I wasn't
 *       able to figure this one out from scratch myself.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINEWIDTH  20
#define TABSIZE    4

static char line[LINEWIDTH];

/*
 * printline()
 * Prints the line until 'pos' column is reached
 */

static void printline(size_t pos) {
    size_t i;
    for (i = 0; i < pos; i++)
        (void)putchar(line[i]);
    if (pos > 0)
        (void)putchar('\n');
}

/*
 * expandtab()
 * Expands a tab into TABSIZE number of blanks
 */

static size_t expandtab(size_t pos) {
    line[pos] = ' ';
    for (++pos; pos < LINEWIDTH && pos % TABSIZE != 0; pos++)
        line[pos] = ' ';
    if (pos < LINEWIDTH)
        return pos;
    else {
        printline(pos);
        return 0;
    }
}

/*
 * findblank()
 * Walks backwards from the current position toward the front of
 * the line looking for the first space character and returns its position
 */

static size_t findblank(size_t pos) {
    while (pos > 0 && line[pos] != ' ')
        pos--;
    if (pos == 0)
        return LINEWIDTH;
    else
        return (pos + 1);
}

/*
 * squish()
 * Copy characters starting at 'pos' to the beginning of the line
 * and return the adjusted value of 'pos'.  This compacts the line
 * leaving any text after 'pos' still in the buffer.
 */

static size_t squish(size_t pos) {
    size_t i = 0;
    size_t j;
    if (pos == 0 || pos >= LINEWIDTH)
        return 0;
    for (j = pos; j < LINEWIDTH; ++j) {
        line[i] = line[j];
        i++;
    }
    return i;
}

int main(void) {

    int    c;
    size_t pos = 0;

    while ((c = getchar()) != EOF) {
        line[pos] = c;
        if (c == '\t') {
            pos = expandtab(pos);
        } else if (c == '\n') {
            printline(pos);
            pos = 0;
        } else if (++pos >= LINEWIDTH) {
            pos = findblank(pos);
            printline(pos);
            pos = squish(pos);
        }
    }

    exit(EXIT_SUCCESS);
}
