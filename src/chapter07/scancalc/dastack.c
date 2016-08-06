/*
* Array-based double-type (floating point) stack (last in, first out "LIFO")
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 100 // Maximum depth of stack

static size_t dstackptr = 0;    // Stack pointer--next free stack position
static double dstack[MAXSTACK]; // Array-based stack of double-typed values

/*
 * dapush(): Push a value onto the top of the stack
 */

void dapush(double val) {
	if (dstackptr < MAXSTACK)
		dstack[dstackptr++] = val;
	else {
		printf("Stack is full\n");
		exit(EXIT_FAILURE);
	}
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

/*
 * dadup(): Duplicates the top two elements on the stack
 */

void dadup(void) {
	if (dstackptr == 0)
		printf("Empty stack\n");
	else if (dstackptr == MAXSTACK)
		printf("Stack is full\n");
	else {
		double temp = dstack[dstackptr - 1];
		dstack[dstackptr++] = temp;
	}
}

/*
 * daswap(): Swaps the top two elements on the stack
 */

void daswap(void) {
	if (dstackptr < 2)
		printf("Less than two items are on the stack\n");
	else {
		double temp;
		temp = dstack[dstackptr - 1];
		dstack[dstackptr - 1] = dstack[dstackptr - 2];
		dstack[dstackptr - 2] = temp;
	}

}

/*
 * dalist(): Lists the items on the stack
 */

void dalist(void) {
	size_t i;
	for (i = 0; i < dstackptr; i++)
		printf("%.8g\n", dstack[i]);
}

/*
 * daclear(): Clears the stack 
 */

void daclear(void) {
	dstackptr = 0;
}

/*
 * dasize(): Returns the size of the stack
 */

size_t dasize(void) {
	return dstackptr;
}