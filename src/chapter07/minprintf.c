/*
* minprintf: minimal printf with variable argument list
*
* NOTE: This is really a mock printf since it leverages printf, but K&R
*       includes it to illustrate variable arguments. 
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * minprintf(): minimal printf with variable argument list
 */

static void minprintf(char *fmt, ...) {
	
	va_list  ap;  // Points to each unnamed arg in turn
	char    *p;
	char    *sval;
	int      ival;
	double   dval;

	va_start(ap, fmt);
	for (p = fmt; *p != '\0'; p++) {

		// unless the current character in the format stream is an
		// '%' then print the character and move on to the next
		if (*p != '%') {
			(void)putchar(*p);
			continue;
		}

		// otherwise, based upon the format code, format and handle
		// the next argument
		switch (*++p) {
			case 'd':
				ival = va_arg(ap, int);
				printf("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval != '\0'; sval++)
					(void)putchar(*sval);
				break;
			default:
				(void)putchar(*p);
				break;
		}
	}
	va_end(ap);
}

/*
 * Main
 */

int main(void) {
	
	minprintf("test of no format\n");
	minprintf("test of integer format ('%%d'): %d\n", 10);
	minprintf("test of double  format ('%%f'): %f\n", 3.14);
	minprintf("test of string  format ('%%s'): \"%s\"\n", "this is a string");
	minprintf("test of multiple args: %d, %f, \"%s\"\n", 10, 3.14, "this is a string");

	exit(EXIT_SUCCESS);
}