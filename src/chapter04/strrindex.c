/**
* strrindex: Returns the position of the rightmost occurrence of t in s
*
* Returns the position of the rightmost occurrence of 't' inside 's' or -1 if 
* not found.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NOT_FOUND -1
#define MAX_STRING 100

/*
 * strindex(): Returns index of leftmost 't' inside 's' or -1 if not found
 */

static int strindex(char s[], char t[]) {

	int i;
	int j;
	int k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			; // Empty
		if (k > 0 && t[k] == '\0')
			return i;
	}

	return NOT_FOUND;
}

/*
 * strrindex(): Returns index of rightmost 't' inside 's' or -1 if not found
 */

static int strrindex(char s[], char t[]) {

	int i;
	int j;
	int k;

	for (i = (int)strlen(s) - (int)strlen(t); s[i] >= 0; i--) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			; // Empty
		if (k > 0 && t[k] == '\0')
			return i;
	}

	return NOT_FOUND;
}

int main(void) {

	char s[] = "This is my test string, but its not much of a test string.";
	char t[MAX_STRING] = "";

	(void)strcpy(t, "test");
	printf("In the string: \"%s\"\n", s);
	printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
	printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));
	(void)putchar('\n');

	(void)strcpy(t, "string");
	printf("In the string: \"%s\"\n", s);
	printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
	printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));
	(void)putchar('\n');

	(void)strcpy(t, "This");
	printf("In the string: \"%s\"\n", s);
	printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
	printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));
	(void)putchar('\n');

	(void)strcpy(t, ".");
	printf("In the string: \"%s\"\n", s);
	printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
	printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));
	(void)putchar('\n');

	(void)strcpy(t, "not in string");
	printf("In the string: \"%s\"\n", s);
	printf("The leftmost  occurrence of \"%s\" is at position %d.\n", t, strindex(s, t));
	printf("The rightmost occurrence of \"%s\" is at position %d.\n", t, strrindex(s, t));

	exit(EXIT_SUCCESS);
}