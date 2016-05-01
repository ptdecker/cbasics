/*
 * expand
 *
 * Expands regex style range shorthand such as "a-z" into the full string
 *
 * Pointer version
 *
 * NOTE: The solution provided in Tondo and Gimpel's "The C Answer Book" is provided in the end
 *       comments.  While this is a much shorter and clever solution, it does not handle ranges
 *       that are decending such as "z-a". The solution below does handle these.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 256

static void expand(char *source, char *target) {

	size_t i;
	int    buffer[3] = {'\0', '\0', '\0'};  // a buffer used to track up to three characters of input
	size_t bufflen = 0;                     // number of characters in the buffer

	// Spin through our input array
	while (*source != '\0') {

		// if buffer isn't full, keep filling it;
		// otherwise, save the first to the target string,
		// shift everything else down, then add the new one
		// to the end to keep it full.
		if (bufflen < 3)
			buffer[bufflen++] = *source;
		else {
			int k;
			*target++ = buffer[0];
			for (k = 1; k < 3; k++)
				buffer[k - 1] = buffer[k];
			buffer[2] = *source;
		}

		// if our buffer contains a range (middle buffer character equals a '-'),
		// then expand out into the taget array the range up to, but not including,
		// the last character and flush the buffer excepting the last character in
		// the range keeping it in the buffer for later
		if (bufflen == 3 && buffer[1] == '-') {
			char temp;
			bool up = (buffer[0] < buffer[2]);
			for (temp = buffer[0]; (up) ? (temp < buffer[2]) : (temp > buffer[2]); temp += (up) ? 1 : -1)
				*target++ = temp;
			buffer[0] = buffer[2]; // save the last buffer item--handles "a-b-c" => "abc" case
			bufflen = 1;
		}

		source++;
	}

	// if there is anything left in the buffer, save it off to the target
	// string too then terminate the target string.
	for (i = 0; i < bufflen; i++)
		*target++ = buffer[i];
	*target = '\0';
}

int main(void) {
	char shortened[MAXSTRING] = "";
	char expanded[MAXSTRING] = "";

	(void)strcpy(shortened, "a-z");
	expand(shortened, expanded);
	printf("Shortened: \"%s\", Expanded: \"%s\"\n", shortened, expanded);

	(void)strcpy(shortened, "az");
	expand(shortened, expanded);
	printf("Shortened: \"%s\", Expanded: \"%s\"\n", shortened, expanded);
	
	(void)strcpy(shortened, "-a---");
	expand(shortened, expanded);
	printf("Shortened: %s, Expanded: %s\n", shortened, expanded);
	
	(void)strcpy(shortened, "-");
	expand(shortened, expanded);
	printf("Shortened: %s, Expanded: %s\n", shortened, expanded);
	
	(void)strcpy(shortened, "");
	expand(shortened, expanded);
	printf("Shortened: %s, Expanded: %s\n", shortened, expanded);
	
	(void)strcpy(shortened, "-a-z0-9az");
	expand(shortened, expanded);
	printf("Shortened: %s, Expanded: %s\n", shortened, expanded);
	
	(void)strcpy(shortened, "a-zZ-A-");
	expand(shortened, expanded);
	printf("Shortened: %s, Expanded: %s\n", shortened, expanded);

	(void)strcpy(shortened, "a-b-c");
	expand(shortened, expanded);
	printf("Shortened: %s, Expanded: %s\n", shortened, expanded);

	
	exit(EXIT_SUCCESS);
}

/*
 * Solution from "The C Answer Book"
 *
 * void expand(char s1[], char s2[]) {
 *     char c;
 *     int  i, j;
 *     i = j = 0;
 *     while ((c = s1[i++]) != '\0') // fetch a char from s1
 *         if (s1[i] == '-' && s1[i+1] >= c) {
 *             i++;
 *             while (c < s1[i])
 *                 s2[j++] = c++; // expand shorthand
 *         } else
 *             s2[j++] = c; // copy the character
 *     s2[j] = '\0';
 * }
 */