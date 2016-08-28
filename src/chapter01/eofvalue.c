/* Exercise 1-6: Determine the value of EOF
 *
 * Verify the expression getchar() != EOF is 0 or 1
 */

// Includes

#include <stdio.h>

/* Main */

int main(void) {

    int result;

    while ((result = getchar()) != EOF)
        printf("%d\n", result);

    printf("EOF is '%d'\n", result);

    return 0;
}
