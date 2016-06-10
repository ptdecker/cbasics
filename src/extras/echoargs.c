/*
* Echo passed arguments
*/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

	while (--argc > 0)
		printf("%s%s", *++argv, (argc > 1) ? " " : "");

	(void)putchar('\n');

	exit(EXIT_SUCCESS);
}