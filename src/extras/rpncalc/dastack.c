/*
 * Array-based double-type (floating point) stack (last in, first out "LIFO")
 */

// Includes

#include <stdio.h>

// Definitions

#define MAXSTACK 100 // Maximum depth of stack

// Globals

static size_t dstackptr = 0;    // Stack pointer--next free stack position
static double dstack[MAXSTACK]; // Array-based stack of double-typed values

/*
 * push(): Push a value onto the top of the stack
 */

void dapush(double val) {
    if (dstackptr < MAXSTACK)
        dstack[dstackptr++] = val;
    else
        printf("Error: Stack is full--Cannot add (push) value '%g' on to it\n", val);
}

/*
 * pop(): Pop the top value from the stack
 */

double dapop(void) {
    if (dstackptr > 0)
        return dstack[--dstackptr];
    printf("Error: Stack is empty--nothing to remove (pop) from it\n");
    return 0.0L;
}
