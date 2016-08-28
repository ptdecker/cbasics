/* Exercise 8-03:  Implements _flushbuf(), fflush(), and fclose().
 *
 * "Design and write _flushbuf, fflush, and fclose."
 */

/*@ -retvalint -type -nullpass */

// Includes

#include <time.h>   // used to time process

#include "minstdio.h"

/* Main */

int main(void) {

    FILE *fp;
    char x;
    clock_t start = clock();

    putstring("Hello World!\n");
    fflush(stdout);

    fp = fopen("results.txt", "w");
    puts("Hello World!", fp);
    fclose(fp);

    fp = fopen("results.txt", "a");
    puts(" (Wow! Deja vu!)\n", fp);
    fclose(fp);

    fp = fopen("results.txt", "r");
    while ((x = getc(fp)) != EOF)
        if (x != '\0')
            putchar(x);
    fclose(fp);
    fflush(stdout);

    // Get out of Dodge City, Kansas returning the running time in ticks
    return (unsigned)(clock() - start);
}
