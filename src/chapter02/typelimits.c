/*
 * Print the limits of the standard C type
 */

#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {

    // Integers fom headers

    printf("From Standard Headers (<limits.h>, <float.h>):\n");
    printf("\tchar bits         : %d\n", CHAR_BIT);
    printf("\tchar              : '%c' (%d) < x < '%c' (%d)\n", CHAR_MIN, (int)CHAR_MIN, CHAR_MAX, (int)CHAR_MAX);
    printf("\tsigned char       : '%c' (%d) < x < '%c' (%d)\n", SCHAR_MIN, (int)SCHAR_MIN, SCHAR_MAX, (int)SCHAR_MAX);
    printf("\tunsigned char     : '%c' (%d) < x < '%c' (%d)\n", 0, 0, UCHAR_MAX, (int)UCHAR_MAX);
    printf("\tshort             : %d < x < %d\n", SHRT_MIN, SHRT_MAX);
    printf("\tunsigned short    : %d < x < %d\n", 0, (int)USHRT_MAX);
    printf("\tint               : %d < x < %d\n", INT_MIN, INT_MAX);
    printf("\tunsigned int      : %u < x < %u\n", 0, UINT_MAX);
    printf("\tlong              : %li < x < %li\n", LONG_MIN, LONG_MAX);
    printf("\tunsigned long     : %lu < x < %lu\n", (unsigned long)0, (unsigned long)ULONG_MAX);

    /*@ignore@*/ // because splint doesn't like 'long long', LLONG_MIN, LLONG_MAX, _ULLONG_MAX
    printf("\tlong long         : %lli < x < %lli\n", (long long)LLONG_MIN, (long long)LLONG_MAX);
    printf("\tunsigned long long: %llu < x < %llu\n", (unsigned long long)0, (unsigned long long)ULLONG_MAX);
    /*@end@*/

    // Floating point from headers

    printf("\tfloat             : %e < x < %e\n", FLT_MIN, FLT_MAX);
    printf("\tdouble float      : %e < x < %e\n", DBL_MIN, DBL_MAX);
    printf("\tlong double       : %Le < x < %Le\n", LDBL_MIN, LDBL_MAX);

    // Computed integers

    printf("Determined by Direct Computation:\n");
    printf("\tchar          : %d < x < %d\n", (int)~(char)((unsigned char) ~0 >> 1), (int)(char)((unsigned char) ~0 >> 1));
    printf("\tunsigned char : %d < x < %d\n", 0, (int)(unsigned char) ~0);
    printf("\tshort         : %d < x < %d\n", (int)~(short)((unsigned short) ~0 >> 1), (int)(short)((unsigned short) ~0 >> 1));
    printf("\tunsigned short: %d < x < %d\n", 0, (int)(unsigned short) ~0);
    printf("\tint           : %d < x < %d\n", ~(int)((unsigned int) ~0 >> 1), (int)((unsigned int) ~0 >> 1));
    printf("\tunsigned int  : %d < x < %d\n", 0, (int)(unsigned int) ~0);
    printf("\tlong          : %li < x < %li\n", ~(long)((unsigned long) ~0 >> 1), (long)((unsigned long) ~0 >> 1));
    printf("\tunsigned long : %lu < x < %lu\n", (unsigned long)0, (unsigned long) ~0);
/*@ignore@*/ // because splint doesn't like 'long long'
    printf("\tlong          : %lli < x < %lli\n", ~(long long)((unsigned long long) ~0 >> 1), (long long)((unsigned long long) ~0 >> 1));
    printf("\tunsigned long : %llu < x < %llu\n", (unsigned long long)0, (unsigned long long) ~0);
/*@end@*/

    return 0;
}
