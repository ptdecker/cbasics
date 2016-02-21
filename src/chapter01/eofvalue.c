/*
 * Determine the value of EOF
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int result;
    while ((result = getchar()) != EOF) {
        printf("%d\n", result);
    }
    printf("EOF is '%d'\n", result);
    exit(EXIT_SUCCESS);
}
