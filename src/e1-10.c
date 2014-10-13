#include <stdio.h>

/* replace tabs, backspaces, and backslashes with '\t', '\b', '\\' */

main () {

   int c;

   while ((c = getchar()) != EOF) {

      if (c == '\t') {
          putchar('\\');
          putchar('t');
      } else if (c == '\b') {
          putchar('\\');
          putchar('b');
      } else if (c == '\\') {
          putchar('\\');
          putchar('\\');
      } else {
          putchar(c);
      }

   }

}
