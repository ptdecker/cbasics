/* Exercise 8-06: A minimal implimentation of malloc() and free() plus a version of calloc()
 *
 * "The standard library function calloc(n,size) returns a pointer to n objects of
 *  size 'size' with the storage initialized to zero. Write calloc, by calling
 *  malloc or by modifying it."
 */

/*@ -nullassign -mustdefine -usedef -branchstate -onlytrans -compmempass -unrecog -statictrans -globstate -type -immediatetrans -noret -mustfreefresh -exportlocal -nullderef -mustfreeonly -nullret -compdef */

#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#define DEBUG

// Includes

#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> // equivalent to (K&R) #include "syscalls.h"

// Definitions

#define NO_MEMORY (-1)
#define NALLOC    1024 // Minimum number of units to request at a time

typedef long Align;          // For alignment to long boundaries

union header {
    struct {
        union header *ptr;   // Next block if on free list
        unsigned long size;  // Size of this block
    } s;
    Align x;                 // Force alignment of blocks
};

typedef union header Header;

// Globals

static Header  base;         // Empty list to get started
static Header *freep = NULL; // Start of free list

/*
 * free(): put block ap in free list
 */

void free(void *ap) {

    Header *bp;
    Header *p;

#ifdef DEBUG
    fprintf(stderr, "free(): freeing up allocated memory at %x\n", (unsigned int)ap);
#endif

    // Point to block header
    bp = (Header *)ap - 1;
    for (p = freep; !(p < bp && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (p < bp || bp < p->s.ptr))
            break;

    // Join to upper nbr
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr   = p->s.ptr->s.ptr;
    } else
        bp->s.ptr   = p->s.ptr;

    // Join to lower nbr
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr   = bp->s.ptr;
    } else
        p->s.ptr   = bp;

    freep = p;
}

/*
 * morecore(): ask system for more memory
 */

static Header *morecore(unsigned long nu) {

    char   *cp;
    Header *up;

#ifdef DEBUG
    fprintf(stderr, "morecore(): grabbing more core, %lu bytes\n", nu * sizeof(Header));
#endif

    if (nu < NALLOC)
        nu = NALLOC;

    if ((cp = sbrk(nu * sizeof(Header))) == (char *)(-1))
        return NULL;

    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up + 1));

    return freep;
}

/*
 * malloc(): general-purpose storage allocator
 */

void *malloc(unsigned long nbytes) {

    Header *p;
    Header *prevp = NULL;
    unsigned long nunits;

#ifdef DEBUG
    fprintf(stderr, "malloc(): allocating %lu bytes\n", nbytes);
#endif

    // Determine how many units we need to allocate
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if (prevp == NULL && freep == NULL) {
        freep       = &base;
        prevp       = &base;
        base.s.ptr  = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {

        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            freep = prevp;
            return (void *)(p + 1);
        }

        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }

}

/*
 * calloc(): allocate n objects of size size
 */

void *calloc(unsigned long n, unsigned long size) {

    unsigned long i;
    unsigned long nb;
    char *p;
    char *q;

    // Calculate size of space that needs to be allocated
    nb = n * size;

#ifdef DEBUG
    fprintf(stderr, "calloc(): attempting to allocate %lu objects size %lu each %lu bytes\n", n, size, nb);
#endif

    // Attempt to allocate the space and, if successful, clear it
    if ((q = malloc(nb)) != NULL)
        for (p = q, i = 0; i < nb; i++)
            *p++ = 0;

    return q;
}

/* Main */

int main(void) {

    void *memptr;

    memptr = malloc(1024);
    fprintf(stdout, "main(): memory allocated at %x\n", (unsigned int)memptr);
    if (memptr != NULL)
        free(memptr);

    memptr = calloc(5, sizeof(double));
    fprintf(stdout, "main(): memory allocated at %x\n", (unsigned int)memptr);
    if (memptr != NULL)
        free(memptr);

    // This next allocation should push us over the limit
    memptr = calloc(1024, 1024);
    fprintf(stdout, "main(): memory allocated at %x\n", (unsigned int)memptr);
    if (memptr != NULL)
        free(memptr);

}
