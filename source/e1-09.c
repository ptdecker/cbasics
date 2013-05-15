#include <stdio.h>

/* replace two or more blanks with a single blank */

main () {

   #define IN  1 /* inside a set of blanks */
   #define OUT 0 /* outside a set of blanks */

   int c;
   int state;

   state = OUT;
   while ((c = getchar()) != EOF) {

      if (c != ' ') {
         state = OUT;
         putchar(c);
      } else if (state != IN) {
         state = IN;
         putchar(c);
      }

   }
}
