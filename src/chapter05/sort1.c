/*
 * sort1:  Sorts input lines supporting reverse and numeric ordering using '-r' and '-n' switches
 */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

/*@ -statictrans -mustfreefresh -nullret -compdef */

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

// Includes

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions

#define ALLOCSIZE 10000000  // Maximum available storage (simulated)
#define MAXLEN        1000  // Maximum length of any input line
#define MAXLINES     10000  // Maximum number of lines to be sorted

// Globals

static char allocbuf[ALLOCSIZE]; // Storage for alloc
static char *allocp = allocbuf;  // Next free position in alloc
static char *lineptr[MAXLINES];  // Pointers to text lines

/*
 * alloc(): rudimentary storage allocator
 */

static char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) { // it fits
        allocp += n;
        return allocp - n; // old p
    }
    return 0; // not enough room
}

/* getline: read an aribitrarily long line placing as much as
 * possible into 's' and returning the full length
 */

static size_t getline(char *s, size_t lim) {

    char c;
    char *sindex = s;

    while (--lim > 0 && (c = (char)getchar()) != (char)EOF && c != '\n')
        *sindex++ = c;
    if (c == '\n')
        *sindex++ = c;
    *sindex = '\0';

    return (size_t)(sindex - s);
}


/*
 * readlines(): read input lines
 */

static int readlines(char *lineptr[], int maxlines) {

    size_t len;
    int    nlines;
    char  *p;
    char   line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {

        if ((p = alloc((int)len)) == NULL || nlines >= maxlines)
            return -1;

        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;

    }

    return nlines;
}

/*
 * writelines(): outputs each string in the passed array of strings
 */

static void writelines(char *lineptr[], int nlines, bool descend) {
    int i;
    if (descend)
        for (i = nlines - 1; i > -1; i--)
            printf("%s\n", lineptr[i]);
    else
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
}

/*
 * swap(): interchanges v[i] and v[j]
 */

static void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/*
 * numcmp(): compares two numbers
 */

static int numcmp(const char *s1, const char *s2) {

    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/*
 * qsort(): sort v[left]...v[right] into increasing order
 */

static void myqsort(void *v[], int left, int right, int (*comp)(void *, void *)) {

    int i;
    int last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last - 1,  comp);
    myqsort(v, last + 1, right, comp);

}

/* Main */

int main(int argc, char *argv[]) {

    int  nlines;          // Number of input lines to read
    bool numeric = false; // 'true' if numeric sort
    bool descend = false; // 'true' if descending output
    char c;

    // Evaluate arguments

    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]) != '\0')
            switch (c) {
                case 'n':
                    numeric = true;
                    break;
                case 'r':
                    descend = true;
                    break;
                default:
                    printf("sort: illegal option %c\n", c);
                    exit(EXIT_FAILURE);
            }

    if (argc == 0) {
        printf("usage: sort -nr [FILE]\n");
        exit(EXIT_FAILURE);
    }

    // Read in the lines into memory

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        printf("Input is too big to sort\n");
        exit(EXIT_FAILURE);
    }

    // Sort

    myqsort(
            (void **) lineptr,
            0,
            nlines - 1,
            (int (*)(void*, void*))(numeric ? numcmp : strcmp)
        );

    // Write out the results

    writelines(lineptr, nlines, descend);

    return 0;
}
