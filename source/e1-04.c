#include <stdio.h>

/* print Celsius-Fahrenheit table with headings
   for fahr = 0, 20, ..., 300 */

main() {

   int fahr, celsius;
   int lower, upper, step;

   lower = 0;   /* lower limit of temperature table */
   upper = 300; /* upper limit */
   step  = 20;  /* step size */

   celsius = lower;
   printf("Celsius\t\tFahrenheit\n");
   while (celsius <= upper) {
      fahr = (9 * celsius) / 5 + 32;
      printf("%6d\t\t%6d\n", celsius, fahr);
      celsius = celsius + step;
   }
}

