/*
 * Print Celsius-Fahrenheit table with headings
 * for fahr = 0, 20, ..., 300
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    double fahr;
    double celsius;
    int    lower =   0;  // lower limit of temperature table
    int    upper = 300;  // upper limit
    int    step  =  20;  // step size

    celsius = (double)lower;
    printf("Celsius\t\tFahrenheit\n");
    while (celsius <= (double)upper) {
        fahr = (9.0 * celsius) / 5.0 + 32.0;
        printf("%3.0f\t\t%6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }

    exit(EXIT_SUCCESS);
 }
