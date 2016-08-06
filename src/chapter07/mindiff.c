/*
* mindiff - Compares two files printing the first line where they differ
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants

#define MAXLINE 10000

/*
 * filecomp(): Compare two files
 */

static void filecomp(FILE *fp1, FILE *fp2) {

	char  line1[MAXLINE];
	char  line2[MAXLINE];
	char *lp1;
	char *lp2;

	// Walk through both files comparing each line by line looking for
	// where they do not match

	do {

		// Get a line from each file (read a line into the line buffer for each file)
		lp1 = fgets(line1, MAXLINE, fp1);
		lp2 = fgets(line2, MAXLINE, fp2);

		// If we were able to read a line from both files, then compare the lines. If
		// they are equal then proceed onward to the next line
		if (lp1 == line1 && lp2 == line2) {
			if (strcmp(line1, line2) != 0) {
				printf("First difference is:\n\n%s\n", line1);
				lp1 = NULL;
				lp2 = NULL;
			}

		// Otherwise, we're at the end of one of the two files so we will print the last
		// line of the file we ended with
		} else if (lp1 != line1 && lp2 == line2)
			printf("End of first file reached at the following line:\n\n%s\n", line2);
		else
			printf("End of second file reached at the following line:\n\n%s\n", line2);
	} while (lp1 == line1 && lp2 == line2);

}

// Main

int main(int argc, char *argv[]) {

	FILE *fp1;
	FILE *fp2;

	// File names must be provided
	if (argc != 3) {
		fprintf(stderr, "mindiff: usage: mindiff <file1> <file2>\n");
		exit(EXIT_FAILURE);
	}

	// Attempt to open the first file
	if ((fp1 = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "mindiff: cannot open file %s\n", *argv);
		exit(EXIT_FAILURE);
	}

	// Attempt to open the second file
	if ((fp2 = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "mindiff: cannot open file %s\n", *argv);
		exit(EXIT_FAILURE);
	}

	// Compare the two files
	filecomp(fp1, fp2);

	// Close the files and exit (exit() closes files)

	exit(EXIT_SUCCESS);
}