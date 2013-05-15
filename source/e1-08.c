#include <stdio.h>

/* Count blanks, tabs, and newlines */

main() {

   int c;
   int blanks, tabs, nl;


   blanks = tabs = nl = 0;

   while ((c = getchar()) != EOF) {

      if (c == ' ')
         ++blanks;
      else if (c == '\t')
         ++tabs;
      else if (c == '\n')
         ++nl;


   }

   printf("%d blanks, %d tabs, %d newlines\n", blanks, tabs, nl);

}

