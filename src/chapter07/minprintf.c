/*
 * minprintf: minimal printf with variable argument list
 *
 * NOTE: This is really a mock printf since it leverages printf, but K&R
 *       includes it to illustrate variable arguments.
 */

// Neither split nor clang like having format string contents unkown at
// complile time, override this concern for purposes of this exercise

/*@ -formatconst */

#pragma clang diagnostic ignored "-Wformat-security"

// Includes

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

// Definitions

#define LOCALFMT 100  // Maximum supported format string length

/*
 * minprintf(): minimal printf with variable argument list
 */

static void minprintf(char *fmt, ...) {

    va_list  ap;  // Points to each unnamed arg in turn
    char    *p;
    char    *sval;
    char     localfmt[LOCALFMT];
    int      i;
    int      ival;
    unsigned uval;
    double   dval;

    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; p++) {

        // unless the current character in the format stream is an
        // '%' then print the character and move on to the next
        if (*p != '%') {
            (void)putchar(*p);
            continue;
        }

        // handle the double '%'
        if (*(p+1) == '%') {
            (void)putchar(*(++p));
            continue;
        }

        // build the format string to be passed on to the real printf
        // from the format string passed to us
        i = 0;
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
                ival = va_arg(ap, int);
                printf(localfmt, ival);
                break;
            case 'x':
            case 'X':
            case 'u':
            case 'o':
                uval = va_arg(ap, unsigned);
                printf(localfmt, uval);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf(localfmt, dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                printf(localfmt, sval);
                break;
            default:
                printf(localfmt);
                break;
        }
    }
    va_end(ap);
}

/* Main */

int main(void) {

    minprintf("test of no format\n");
    minprintf("test of integer format ('%%d'): %d\n", 10);
    minprintf("test of double  format ('%%f'): %f\n", 3.14);
    minprintf("test of string  format ('%%s'): \"%s\"\n", "this is a string");
    minprintf("test of hex     format ('%%x'): %x\n", 65534);
    minprintf("test of complex format ('[%%-15.10s]'): [%-15.10s]\n", "hello world!");
    minprintf("test of multiple args: %d, %f, \"%s\"\n", 10, 3.14, "this is a string");

    return 0;
}
