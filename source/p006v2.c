#include <stdio.h>
#include <ncurses.h>

main()
{
	printf("\e[2J");		/* clear screen */
	printf("\e[1;1H");		/* position 1,1 */
	printf("\e[1m");		/* bold */
	printf("Hello");
	printf("\e[0m");		/* clear */
	printf(" world! (Todd style)\n");
}
