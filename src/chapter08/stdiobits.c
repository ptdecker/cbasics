// The approach taken with the 'minstdio0' based upon bit fields is slower (142 clock ticks vs 129) and the compiled
// binary is larger (9,976 bytes vs 9,968) than the approach taken by 'minstdio' which uses bit manipulation

/*@ -retvalint -type -retvalother -nullpass */

#include <time.h>   // used to time process

#include "minstdio0.h"

int main(void) {

	FILE *fp;
	char x;
	clock_t start = clock();

	putstring("Hello World!\n");
	fflush(stdout);

	fp = fopen("results.txt", "w");
	puts("Hello World!", fp);
	fclose(fp);

	fp = fopen("results.txt", "a");
	puts(" (Wow! Deja vu!)\n", fp);
	fclose(fp);

	fp = fopen("results.txt", "r");
	while ((x = getc(fp)) != EOF)
		if (x != '\0')
			putchar(x);
	fclose(fp);
	fflush(stdout);

	// Get out of Dodge City, Kansas returning the running time in ticks
	return (unsigned)(clock() - start);
}
