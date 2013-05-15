#include <stdio.h>

/* Verify that the expression getchar() != EOF is 0 or 1 */

main() {

   int result;

   while (result = (getchar() != EOF))
      printf("%d\n", result);

   printf("%d\n", result);

}

