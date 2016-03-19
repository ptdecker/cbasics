/*
 * Print a Fehrenheit to Celsius table
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    double fahr;
    double celsius;
    int    lower =   0;
    int    upper = 300;
    int    step  =  20;

    printf("Fahrenheit\tCelsius\n");
    fahr = (double)lower;
    while (fahr <= (double)upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f\t\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    exit(EXIT_SUCCESS);
}
