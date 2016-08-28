/*
 * minfind: print lines that match a pattern passed in the first argument with
 *          optional line numbering
 */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

// Includes

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions

#define MAXLINE 1000

/*
 * findpat(): Find a pattern in a file
 */

static void findpat(FILE *fp, char *fname, char *pattern, bool except, bool number) {

    char     line[MAXLINE] = "";
    unsigned lineno = 0;

    // Search for pattern, or non-pattern, adding line numbers if appropriate

    while (fgets(line, MAXLINE, fp) != NULL) {
        lineno++;
        if ((strstr(line, pattern) != NULL) ^ except) {
            if (*fname != '\0')
                printf("%s - ", fname);
            if (number)
                printf("%u: ", lineno);
            printf("%s", line);
        }
    }
}

/* Main */

int main(int argc, char *argv[]) {

    char  pattern[MAXLINE];
    int   c;
    bool  except = false;
    bool  number = false;
    FILE *fp;

    // Evaluate optional switch arguments

    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]) != '\0')
            switch (c) {
                case 'x':
                    except = true;
                    break;
                case 'n':
                    number = true;
                    break;
                default:
                    fprintf(stderr, "minfind: illegal option %c\n", c);
                    exit(EXIT_FAILURE);
            }

    // Check for valid usage (at least a pattern argument should still remain)

    if (argc < 1) {
        fprintf(stderr, "Usage: minfind [-x] [-n] pattern [file ...]\n");
        exit(EXIT_FAILURE);
    }

    // Save search pattern

    strcpy(pattern, *argv);

    // If no more arguments remain, read from standard input

    if (argc == 1) {
        findpat(stdin, "", pattern, except, number);
        exit(EXIT_SUCCESS);
    }

    // Arguments do remain, so try to process them as if they are file names
    // searching each in turn for the pattern

    while (--argc > 0) {

        // Attempt to open the file

        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "minfind: cannot open %s\n", *argv);
            exit(EXIT_FAILURE);
        }

        // Search the file

        findpat(fp, *argv, pattern, except, number);
        (void)fclose(fp);
    }

    exit(EXIT_SUCCESS);
}
