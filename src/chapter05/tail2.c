/*
* Tail
*/

// The following definition change is needed to allow the use of getline() in this
// example without having to call it something else.
// c.f. http://stackoverflow.com/questions/37474117/how-to-implement-custom-versions-of-the-getline-function-in-stdio-h-clang-os-x

/*@ -branchstate */

#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFLINES 10 // Default number of lines to print
#define LINES    100 // Maximum number of lines to print
#define MAXLEN   1000 // Maximum length of an input line

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
 * error(): print error messages
 */

static void error(char *s) {
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}

/*
 * Main
 */

int main(int argc, char *argv[]) {

	// Define variables

	char  *buf;            // Buffer
	char  *p;              // Current position in the buffer
	char  *bufend;         // End of the buffer
	char   line[MAXLEN];   // Current input line
	char  *lineptr[LINES]; // Lines read
	int    first;          // Index of first line
	int    last = 0;       // Index of last line read
	size_t len;            // Length of line returned by getline
	int    n = DEFLINES;   // Number of lines to print
	int    nlines = 0;     // Number of lines read
	int    i;              // Loop index

	// Read arguments

	if (argc == 1)
		n = DEFLINES;
	else if (argc == 2 && (*++argv)[0] == '-')
		n = atoi(argv[0] + 1);
	else
		error("usage:  tail [-n]");

	// Finish initalizations

	if (n < 1 || n > LINES)
		n = LINES;

	for (i = 0; i < LINES; i++)
		lineptr[i] = NULL;

	if ((buf = malloc(LINES * MAXLEN)) == NULL)
		error("tail: cannot allocate buffer");

	p = buf;
	bufend = buf + LINES * MAXLEN;

	// Read the input buffering lines in the process

	while ((len = getline(line, MAXLEN)) > 0) {

		// We are going to go past the end of the buffer so wrap around instead
		if (p + len + 1 >= bufend)
			p = buf;

		// Add the line we read to the buffer
		lineptr[last] = p;
		strcpy(lineptr[last], line);

		//  Move the index to the last line read forward. If it exceeds the max
		//  number of lines, wrap it around too
		if (++last >= LINES)
			last = 0;

		// Move to start of where next line should be read
		p += len + 1;

		// And increase our overall line count
		nlines++;
	}

	// If we read less lines than the number requested, adjust requested line count down

	if (n > nlines)
		n = nlines;

	// Determine line to start printing from accounting for any wrap around that might
	// have occurred

	first = last - n;
	if (first < 0)
		first += LINES;

	// Print the line wrapping around to the beginning if the end is reached

	for (i = first; n-- > 0; i = (i + 1) % LINES)
		printf("%s", lineptr[i]);

    return 0;
}