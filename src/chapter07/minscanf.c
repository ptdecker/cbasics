/*
* minprintf: minimal scanf with variable argument list
*
* NOTE: This is really a mock scanf since it leverages scanf, but K&R
*       includes it to illustrate variable arguments. 
*/

// Neither split nor clang like having format string contents unkown at
// complile time, override this concern for purposes of this exercise
/*@ -formatconst */
#pragma clang diagnostic ignored "-Wformat-security"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#define LOCALFMT 100  // Maximum supported format string length

/*
 * minprintf(): minimal printf with variable argument list
 */

static void minscanf(char *fmt, ...) {
	
	va_list   ap;  // Points to each unnamed arg in turn
	char     *p;
	char     *sval;
	char      localfmt[LOCALFMT];
	int       i = 0;
	int      *ival;
	unsigned *uval;
	double   *dval;

	va_start(ap, fmt);
	for (p = fmt; *p != '\0'; p++) {

		// unless the current character in the format stream is an
		// '%' then print the character and move on to the next
		if (*p != '%') {
			localfmt[i++] = *p;
			continue;
		}

		// handle the double '%'
		if (*(p+1) == '%') {
			localfmt[i++] = *(++p);
			continue;
		}

		// build the format string to be passed on to the real printf
		// from the format string passed to us
		localfmt[i++] = '%';
		while (*(p+1) != '\0' && !isalpha(*(p+1)))
			localfmt[i++] = *++p;
		localfmt[i++] = *(p+1);
		localfmt[i] = '\0';

		// otherwise, based upon the format code, format and handle
		// the next argument
		switch (*++p) {
			case 'd':
			case 'i':
				ival = va_arg(ap, int *);
				(void)scanf(localfmt, ival);
				break;
			case 'x':
			case 'X':
			case 'u':
			case 'o':
				uval = va_arg(ap, unsigned *);
				(void)scanf(localfmt, uval);
				break;
			case 'f':
				dval = va_arg(ap, double *);
				(void)scanf(localfmt, dval);
				break;
			case 's':
				sval = va_arg(ap, char *);
				(void)scanf(localfmt, sval);
				break;
			default:
				(void)scanf(localfmt);
				break;
		}
		i = 0;
	}
	va_end(ap);
}

/*
 * Main
 */

int main(void) {

	char     sval[100] = "";
	int      ival = 0;
	unsigned uval = 0;
	double   dval = 0.0;
	
	printf("test of integer input ('%%d'): ");
	minscanf("%d", &ival);
	printf("received: %d\n", ival);
	
	printf("test of double input ('%%f'): ");
	minscanf("%f", &dval);
	printf("received: %f\n", dval);
	
	printf("test of string input ('%%s'): ");
	minscanf("%s", sval);
	printf("received: %s\n", sval);
	
	printf("test of hex input ('%%x'): ");
	minscanf("%x", &uval);
	printf("received: %x\n", uval);

	return 0;
}