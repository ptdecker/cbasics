/*
 * escape.c
 *
 * Pointer version
 *
 * Converts special characters in a string to and from escape sequences
 */

#include <stdio.h>
#include <stdlib.h>

static void escape(char *source, char *target) {
	while (*source != '\0') {
    	switch (*source) {
        	case '\a':  // Alarm (Beep, bell character) (\a)
	        	*target++ = '\\';
	        	*target++ = 'a';
	        	break;
        	case '\b':  // Backspace (\b)
	        	*target++ = '\\';
	        	*target++ = 'b';
	        	break;
        	case '\f':  // Formfeed (\f)
	        	*target++ = '\\';
	        	*target++ = 'f';
	        	break;
        	case '\n':  // Newline (Linefeed) (\n)
	        	*target++ = '\\';
	        	*target++ = 'n';
	        	break;
        	case '\r':  // Carriage return (\r)
	        	*target++ = '\\';
	        	*target++ = 'r';
	        	break;
        	case '\t':  // Tab (\t)
	        	*target++ = '\\';
	        	*target++ = 't';
	        	break;
        	case '\v':  // Vertical tab (\v)
	        	*target++ = '\\';
	        	*target++ = 'v';
	        	break;
        	case '\\': // Backslash (\\)
	        	*target++ = '\\';
	        	*target++ = '\\';
	        	break;
        	case '\'': // Single quote (\')
	        	*target++ = '\\';
	        	*target++ = '\'';
	        	break;
        	case '\"':  // Double quote (\")
	        	*target++ = '\\';
	        	*target++ = '\"';
	        	break;
        	case '\?':  // Question mark (\?)
	        	*target++ = '\\';
	        	*target++ = '?';
	        	break;
        	default:
            	*target++ = *source;
    	} // switch
    	source++;
    } // while
    *target = '\0';
} // escape()

static void unescape(char *source, char *target) {
	while (*source != '\0') {
		if (*source != '\\')
			*target++ = *source;
		else {
		    switch (*(++source)) { // Switch on the next character after a confirmed '\'
        		case 'a':  // Alarm (Beep, bell character)
        			*target++ = '\a';
            		break;
        		case 'b':  // Backspace
        			*target++ = '\b';
            		break;
        		case 'f':  // Formfeed
        			*target++ = '\f';
            		break;
        		case 'n':  // Newline (Linefeed)
        			*target++ = '\n';
            		break;
        		case 'r':  // Carriage return
        			*target++ = '\r';
            		break;
        		case 't':  // Tab
        			*target++ = '\t';
           			break;
        		case 'v':  // Vertical tab
        			*target++ = '\v';
            		break;
        		case '\'': // Single quote
        			*target++ = '\'';
            		break;
        		case '"':  // Double quote
        			*target++ = '\"';
            		break;
        		case '?':  // Question mark
        			*target++ = '\?';
            		break;
        		default:
        			*target++ = *source;
    		} // switch
    	} // if-else
    	*target = '\0';
    	source++;
	} // while
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
}