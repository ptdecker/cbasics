/*
 * escape.c
 *
 * Converts special characters in a string to and from escape sequences
 */

#include <stdio.h>

static void escape(char source[], char target[]) {

	size_t i;
	size_t j;

	for (i = 0, j = 0; source[i] != '\0'; i++)
    	switch (source[i]) {
        	case '\a':  // Alarm (Beep, bell character) (\a)
	        	target[j++] = '\\';
	        	target[j++] = 'a';
	        	break;
        	case '\b':  // Backspace (\b)
	        	target[j++] = '\\';
	        	target[j++] = 'b';
	        	break;
        	case '\f':  // Formfeed (\f)
	        	target[j++] = '\\';
	        	target[j++] = 'f';
	        	break;
        	case '\n':  // Newline (Linefeed) (\n)
	        	target[j++] = '\\';
	        	target[j++] = 'n';
	        	break;
        	case '\r':  // Carriage return (\r)
	        	target[j++] = '\\';
	        	target[j++] = 'r';
	        	break;
        	case '\t':  // Tab (\t)
	        	target[j++] = '\\';
	        	target[j++] = 't';
	        	break;
        	case '\v':  // Vertical tab (\v)
	        	target[j++] = '\\';
	        	target[j++] = 'v';
	        	break;
        	case '\\': // Backslash (\\)
	        	target[j++] = '\\';
	        	target[j++] = '\\';
	        	break;
        	case '\'': // Single quote (\')
	        	target[j++] = '\\';
	        	target[j++] = '\'';
	        	break;
        	case '\"':  // Double quote (\")
	        	target[j++] = '\\';
	        	target[j++] = '\"';
	        	break;
        	case '\?':  // Question mark (\?)
	        	target[j++] = '\\';
	        	target[j++] = '?';
	        	break;
        	default:
            	target[j++] = source[i];
    	} // switch

    target[j] = '\0';

} // escape()

static void unescape(char source[], char target[]) {

	size_t i;
	size_t j;

	for (i = 0, j = 0; source[i] != '\0'; i++) {

		if (source[i] != '\\')
			target[j++] = source[i];
		else
		    switch (source[++i]) {
        		case 'a':  // Alarm (Beep, bell character)
        			target[j++] = '\a';
            		break;
        		case 'b':  // Backspace
        			target[j++] = '\b';
            		break;
        		case 'f':  // Formfeed
        			target[j++] = '\f';
            		break;
        		case 'n':  // Newline (Linefeed)
        			target[j++] = '\n';
            		break;
        		case 'r':  // Carriage return
        			target[j++] = '\r';
            		break;
        		case 't':  // Tab
        			target[j++] = '\t';
           			break;
        		case 'v':  // Vertical tab
        			target[j++] = '\v';
            		break;
        		case '\'': // Single quote
        			target[j++] = '\'';
            		break;
        		case '"':  // Double quote
        			target[j++] = '\"';
            		break;
        		case '?':  // Question mark
        			target[j++] = '\?';
            		break;
        		default:
        			target[j++] = source[i];
    		} // switch

    	target[j] = '\0';
	} // for

} // unescape()

int main(void) {

	char teststr1[100] = "This is a test string of special characters: \\a, \\b, \\f, \\n, \\r, \\t, \\v, \\', \\\", \\?";
	char teststr2[100];
	char teststr3[100];

	unescape(teststr1, teststr2);
	escape(teststr2, teststr3);

	printf("Test String 1: %s\n", teststr1);
	printf("Test String 2: %s\n", teststr2);
	printf("Test String 3: %s\n", teststr3);

	return 0;
}