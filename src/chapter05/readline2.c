/*
* Exercise 5-07: Speed comparision of 'readline' variations
*
* Version that stores in an array provided by readline.
* Timing compared: readline2 is 7.5% faster than readline.
*/

/*@ -compdef */

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

// Library includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants

#define ALLOCSIZE 100000  // Maximum available storage (simulated)
#define MAXLEN      1000  // Maximum length of any input line
#define MAXLINES     100  // Maximum number of lines

// Globals

static char *lineptr[MAXLINES];         // Pointers to text lines

/* getbigline: read an aribitrarily long line placing as much as
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
 * swap(): interchanges v[i] and v[j]
 */

static void swap(char *v[], int i, int j) {
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/*
 * qsort(): sort v[left] to v[right] into increasing order
 */

static void myqsort(char *v[], int left, int right) {
	int i, last;

	// Do nothing if the array contains fewer than two elements
	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);

	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);

	myqsort(v, left, last - 1);
	myqsort(v, last + 1, right);
}

/*
 * writelines(): outputs each string in the passed array of strings
 */

static void writelines(char *lineptr[], int nlines) {
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/*
 * readlines1(): read input lines
 */

static int readlines(char *lineptr[], char *linestore, int maxlines) {

	size_t len;
	int    nlines = 0;
	char   line[MAXLEN];
	char  *p = linestore;
	char  *linestop = line + ALLOCSIZE;

	while ((len = getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || p + len > linestop)
			return -1;

		line[len - 1] = '\0';  // Delete newline
		strcpy(p, line);
		lineptr[nlines++] = p;
		p += len;
	}

	return nlines;
}


int main(void) {

	int     nlines;
	clock_t start;
	char    linestore[ALLOCSIZE];

	start = clock();
	if ((nlines = readlines(lineptr, linestore, MAXLINES)) >= 0) {
		myqsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		printf("Run time: %u clock ticks\n", (unsigned)(clock() - start));
		exit(EXIT_SUCCESS);
	}

	printf("Error: Input is too big to sort");
    return EXIT_FAILURE;
}