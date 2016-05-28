/*
* datetools.c
*
* Adds error checking to day_of_year() and month_day()
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

	int i;

	if ((year < 0) || (month < 1) || (month > 12) || (day < 1) || (day > daytab[isleap(year)][month]))
		return -1;

	for (i = 1; i < month; i++)
		day += daytab[isleap(year)][i];

	return day;
}

/*
 * month_day(): set the month and day based upon the day of the year for a specified year
 */

static void month_day(int year, int yearday, int *pmonth, int *pday) {

	int i;

	if ((year < 0) || (yearday < 1) || (yearday > (isleap(year) ? 366 : 365))) {
		*pmonth = -1;
		*pday   = -1;
	    return;
	}

	for (i = 1; yearday > daytab[isleap(year)][i]; i++)
		yearday -= daytab[isleap(year)][i];

	*pmonth = i;
	*pday   = yearday;
}

int main(void) {

	int month, day;

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
	printf("Day %03d occurs in month %02d on day %02d of year %04d\n", 217, month, day, 1966);
	month_day(2000,   1, &month, &day);
	printf("Day %03d occurs in month %02d on day %02d of year %04d\n",   1, month, day, 2000);
	month_day(1999, 365, &month, &day);
	printf("Day %03d occurs in month %02d on day %02d of year %04d\n", 365, month, day, 1999);
	month_day(2000, 366, &month, &day);
	printf("Day %03d occurs in month %02d on day %02d of year %04d\n", 366, month, day, 2000);
	month_day(3000, 365, &month, &day);
	printf("Day %03d occurs in month %02d on day %02d of year %04d\n", 365, month, day, 3000);
	month_day(2004, 366, &month, &day);
	printf("Day %03d occurs in month %02d on day %02d of year %04d\n", 366, month, day, 2004);
	(void)putchar('\n');


	month_day(  -1, 365, &month, &day);
	printf("Attempting a negative year returns                                 : month %d, day %d\n", month, day);
	month_day(2004,   0, &month, &day);
	printf("Attempting a day number less than one returns                      : month %d, day %d\n", month, day);
	month_day(2004, 367, &month, &day);
	printf("Attempting a day number greater than 366 returns                   : month %d, day %d\n", month, day);
	month_day(2003, 366, &month, &day);
	printf("Attempting a day number greater than 365 in a non-leap year returns: month %d, day %d\n", month, day);


	exit(EXIT_SUCCESS);
}