/*
 * fprint: prints a set of files with header, footer, page breaks, and page numbers
 */

// Includes

#include <stdio.h>
#include <stdlib.h>

// Definitions

#define MAXFOOT 3    // Number of footer lines
#define MAXHEAD 5    // Header lines
#define MAXLINE 1000 // Maximum size of one line
#define MAXPAGE 66   // Maximum number of lines on a page

/*
 * header(): print the header
 */

static int header(char *fname, int pageno) {

    int ln = 3;

    fprintf(stdout, "\n\n%s\t(page %d)\n", fname, pageno);
    while (ln++ < MAXHEAD)
        fprintf(stdout, "\n");

    return ln;
}

/*
 * footer(): print the footer
 */

static void footer(void) {
    fprintf(stdout, "\f");
}

/*
 * fileprint(): print a file
 */

static void fileprint(FILE *fp, char *fname) {

    int  lineno = 1;
    int  pageno = 1;
    char line[MAXLINE];

    while (fgets(line, MAXLINE, fp) != NULL) {

        // Header
        if (lineno == 1) {
            lineno = header(fname, pageno);
        }

        // Body
        (void)fputs(line, stdout);

        // Footer
        if (++lineno > MAXPAGE - MAXFOOT) {
            footer();
            lineno = 1;
            pageno++;
        }
    }
    fprintf(stdout, "\f");

}

/* Main */

int main(int argc, char *argv[]) {

    FILE *fp;

    if (argc == 1) {
        fileprint(stdin, "stdin");
        exit(EXIT_SUCCESS);
    }

    while (--argc > 0) {

        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "fprint: cannot open %s\n", *argv);
            exit(EXIT_FAILURE);
        }

        fileprint(fp, *argv);
        (void)fclose(fp);
    }

    exit(EXIT_SUCCESS);
}
