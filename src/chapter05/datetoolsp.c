/*
* datetools.c
*
* Adds error checking to day_of_year() and month_day()
*/

/*@ -unqualifiedtrans -mustfreefresh */

#include <stdbool.h>
#include <stdio.h>

// NOTE: The construct 'isleap(year) ? 1 : 0' could just be expressed as 'isleap(year)' however since isleap() is
//       defined as a bool and arrays expect integer-based indexes, the later approach throws a type mismatch 
//       warning in splint. The former construct clears this error and makes explicit which array index is used
//       depending upon the return value of 'isleap()'

static char daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/*
 * isleap(): returns true if the passed year is a leap year
 */

static bool isleap(int year) {
	return ((year % 4 == 0) && (year % 100) != 0) || (year % 400 == 0);
}

/*
 * day_of_year(): determine the day of the year based upon a year, month, and day
 */

static int day_of_year(int year, int month, int day) {

	char *p;

	if ((year < 0) || (month < 1) || (month > 12) || (day < 1) || (day > daytab[isleap(year) ? 1 : 0][month]))
		return -1;

	p = daytab[isleap(year) ? 1 : 0];
	while (--month > 0)
		day += *++p;

	return day;
}

/*
 * month_day(): set the month and day based upon the day of the year for a specified year
 */

static void month_day(int year, int yearday, int *pmonth, int *pday) {

	char *p;

	if ((year < 0) || (yearday < 1) || (yearday > (isleap(year) ? 366 : 365))) {
		*pmonth = -1;
		*pday   = -1;
	    return;
	}

	p = daytab[isleap(year) ? 1 : 0];
	while (yearday > *++p)
		yearday -= *p;

	*pmonth = p - *(daytab + (isleap(year) ? 1 : 0));
	*pday   = yearday;
}

/*
 * month_name(): returns the name of the n-th month
 */

static void *month_name(int month) {

	static char *name[] = {
		"Illegal month",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	return (month < 1 || month > 12) ? name[0] : name[month];
}

int main(void) {

	int month = 0;
	int day = 0;

	printf("Aug 05, 1966, is day %03d of the year\n", day_of_year(1966,  8,  5));
	printf("Jan 01, 2000, is day %03d of the year\n", day_of_year(2000,  1,  1));
	printf("Dec 31, 1999, is day %03d of the year\n", day_of_year(1999, 12, 31));
	printf("Dec 31, 2000, is day %03d of the year\n", day_of_year(2000, 12, 31));
	printf("Dec 31, 3000, is day %03d of the year\n", day_of_year(3000, 12, 31));
	printf("Dec 31, 2004, is day %03d of the year\n", day_of_year(2004, 12, 31));
	(void)putchar('\n');

	printf("Attempting a negative year returns                             : %d\n", day_of_year(  -1,  8,  5));
	printf("Attempting a month number less than one returns                : %d\n", day_of_year(1966,  0,  5));
	printf("Attempting a month number greater than 12 returns              : %d\n", day_of_year(1966, 13,  5));
	printf("Attempting a day number less than one returns                  : %d\n", day_of_year(1966,  8,  0));
	printf("Attempting a day greater than 31 returns                       : %d\n", day_of_year(1966,  8, 32));
	printf("Attempting a day greater than 30 in April returns              : %d\n", day_of_year(1966,  4, 31));
	printf("Attempting a day greater than 29 in February returns           : %d\n", day_of_year(1966,  2, 30));
	printf("Attempting a day greater than 28 in a non-leap February returns: %d\n", day_of_year(1999,  2, 29));
	(void)putchar('\n');

	month_day(1966, 217, &month, &day);
	printf("Day %03d occurs %s %02d of year %04d\n", 217, month_name(month), day, 1966);
	month_day(2000,   1, &month, &day);
	printf("Day %03d occurs %s %02d of year %04d\n",   1, month_name(month), day, 2000);
	month_day(1999, 365, &month, &day);
	printf("Day %03d occurs %s %02d of year %04d\n", 365, month_name(month), day, 1999);
	month_day(2000, 366, &month, &day);
	printf("Day %03d occurs %s %02d of year %04d\n", 366, month_name(month), day, 2000);
	month_day(3000, 365, &month, &day);
	printf("Day %03d occurs %s %02d of year %04d\n", 365, month_name(month), day, 3000);
	month_day(2004, 366, &month, &day);
	printf("Day %03d occurs %s %02d of year %04d\n", 366, month_name(month), day, 2004);
	(void)putchar('\n');

	month_day(  -1, 365, &month, &day);
	printf("Attempting a negative year returns                                 : month %d, day %d\n", month, day);
	month_day(2004,   0, &month, &day);
	printf("Attempting a day number less than one returns                      : month %d, day %d\n", month, day);
	month_day(2004, 367, &month, &day);
	printf("Attempting a day number greater than 366 returns                   : month %d, day %d\n", month, day);
	month_day(2003, 366, &month, &day);
	printf("Attempting a day number greater than 365 in a non-leap year returns: month %d, day %d\n", month, day);
	(void)putchar('\n');

	printf("The month name of a month less than '1' is '%s'\n", month_name(0));
	printf("The month name of a month greater than '12' is '%s'\n", month_name(13));

	return 0;
}