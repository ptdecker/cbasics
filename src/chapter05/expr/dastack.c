/*
* Array-based double-type (floating point) stack (last in, first out "LIFO")
*/

#include <stdio.h>

#define MAXSTACK 100 // Maximum depth of stack

static size_t dstackptr = 0;    // Stack pointer--next free stack position
static double dstack[MAXSTACK]; // Array-based stack of double-typed values

/*
 * dapush(): Push a value onto the top of the stack
 */

void dapush(double val) {
	if (dstackptr < MAXSTACK)
		dstack[dstackptr++] = val;
	else
		printf("Stack is full\n");
}

/*
 * dapop(): Pop the top value from the stack
 */

double dapop(void) {
	if (dstackptr > 0)
		return dstack[--dstackptr];
	printf("Empty stack\n");
	return 0.0L;
}

/*
 * dapeek(): Return top value from the stack wwithouth popping it
 */

double dapeek(void) {
	if (dstackptr > 0)
		return dstack[(dstackptr - 1)];
	printf("Empty stack\n");
	return 0.0L;
}
