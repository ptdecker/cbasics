/*
 * expand
 *
 * Expands regex style ranges such as "a-z"
 *
 * NOTE: The solution provided in Tondo and Gimpel's "The C Answer Book" is provided in the end
 *       comments.  While this is a much shorter and clever solution, it does not handle ranges
 *       that are decending such as "z-a". The solution below does handle these.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXSTRING 256

static void expand(char source[], char target[]) {
	
	int i, j;                            // loop indexes
	int buffer[3] = {'\0', '\0', '\0'};  // a buffer used to track up to three characters of input
	int bufflen = 0;                     // number of characters in the buffer

	// Spin through our input array
	for (i = 0, j = 0; source[i] != '\0'; i++) {

		// if buffer isn't full, keep filling it;
		// otherwise, save the first to the target string,
		// shift everything else down, then add the new one
		// to the end to keep it full.
		if (bufflen < 3)
			buffer[bufflen++] = source[i];
		else {
			int k;
			target[j++] = buffer[0];
			for (k = 1; k < 3; k++)
				buffer[k - 1] = buffer[k];
			buffer[2] = source[i];
		}

		// if our buffer contains a range (middle buffer character equals a '-'),
		// then expand out into the taget array the range up to, but not including,
		// the last character and flush the buffer excepting the last character in
		// the range keeping it in the buffer for later
		if (bufflen == 3 && buffer[1] == '-') {
			char temp;
			bool up = (buffer[0] < buffer[2]);
			for (temp = buffer[0]; (up) ? (temp < buffer[2]) : (temp > buffer[2]); temp += (up) ? 1 : -1)
				target[j++] = temp;
			buffer[0] = buffer[2]; // save the last buffer item--handles "a-b-c" => "abc" case
			bufflen = 1;
		}
	}

	// if there is anything left in the buffer, save it off to the target
	// string too then terminate the target string.
	for (i = 0; i < bufflen; i++)
		target[j++] = buffer[i];
	target[j] = '\0';
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