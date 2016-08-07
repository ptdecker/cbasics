/*
 * Determine the value of EOF
 */

#include <stdio.h>

int main(void) {

    int result;

    while ((result = getchar()) != EOF)
        printf("%d\n", result);
    
    printf("EOF is '%d'\n", result);

    return 0;
}
