/*
 * Array-based char-type (floating point) stack (last in, first out "LIFO")
 */

// Includes

#include <stdio.h>
#include <stdbool.h>

// Definitions

#define MAXSTACK 100 // Maximum depth of stack

// Globals

static size_t cstackptr = 0;    // Stack pointer--next free stack position
static char   cstack[MAXSTACK]; // Array-based stack of char-typed values

/*
 * capush(): Push a char-type value onto the top of the stack
 */

void capush(char val) {
    if (cstackptr < MAXSTACK) {
        cstack[cstackptr++] = val;
    } else
        printf("Error: Stack is full--Cannot add (push) value '%c' on to it\n", val);
}

/*
 * capop(): Pop the char-type top value from the stack
 */

char capop(void) {
    if (cstackptr > 0)
        return cstack[--cstackptr];
    printf("Error: Stack is empty--nothing to remove (pop) from it\n");
    return '\0';
}

/*
 * casize(): Returns the size of the stack
 */

static size_t casize(void) {
    return cstackptr;
}

/*
 * caempty(): Tests to see if the stack is empty (true = empty)
 */

bool caempty(void) {
    return (casize() == 0);
}
