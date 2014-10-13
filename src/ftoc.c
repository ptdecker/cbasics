/*
 * Print a Fehrenheit to Celsius table
 */

#include <stdio.h>

int main() {

    double fahr;
    double celsius;
    int    lower =   0;
    int    upper = 300;
    int    step  =  20;

    printf("Fahrenheit\tCelsius\n");
    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f\t\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

}
