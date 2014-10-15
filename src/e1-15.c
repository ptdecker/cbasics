/*
 * Print Fahrenheit-Celsius table using a function
 */

#include <stdio.h>

/* Function prototypes */

int ftoc(int ftemp);

/* Main */

int main() {

	int fahr;
	int lower = 0;   /* lower limit of temperature table */
	int upper = 300; /* upper limit */
	int step  = 20;  /* step size */

	for (fahr = lower; fahr <= upper; fahr += step)
		printf("%d\t%d\n", fahr, ftoc(fahr));

}

/* Fahrenheit-Celsius conversion */

int ftoc(int ftemp) {
	return 5 * (ftemp - 32) / 9;
}
