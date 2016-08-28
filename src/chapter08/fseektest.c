/* Exercise 8-04: Implementation of fseek()
 *
 * "The standard library function
 *
 *        int fseek(FILE *fp, long offset, int origin)
 *
 *  is identical to lseek except that fp is a file pointer instead of a file
 *  descriptor and the return value is an int status, not a position.  Write
 *  fseek.  Make sure that your fseek coordinates properly with the buffering
 *  done for the other functions of the library."
 */

/*@ -retvalint -type -nullpass */

// Includes

#include <time.h>   // used to time process

#include "minstdio1.h"

/* Main */

int main(void) {

    FILE *fp;
    char x;
    int  pos;
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

    fp = fopen("results.txt", "a");
    pos = fseek(fp, 14, 0);
    puts("Deja vu--NOT", fp);
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
