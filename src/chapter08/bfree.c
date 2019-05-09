/* Exerise 8-08: Adds bfree() to malloc()
 *
 * "Write a routine bfree(p,n) that will free an arbitary block p of n characters
 * into the free list maintained by malloc and free.  By using bfree, a user can add
 * a static or external array to the free list at any time."
 */

/*@ -nullassign -mustdefine -usedef -branchstate -onlytrans -compmempass -unrecog -statictrans -globstate -type -immediatetrans -noret -mustfreefresh -exportlocal -mustfreeonly -nullret -compdef -temptrans -nullpass */

#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#define DEBUG

// Includes

#include <stdarg.h>
#include <stdio.h>
#include <fcntl.h>

#define __USE_XOPEN_EXTENDED
#include <unistd.h> // equivalent to (K&R) #include "syscalls.h"

// Definitions

#define NO_MEMORY (-1)
#define NALLOC    1024             // Minimum number of units to request at a time
#define MAXBYTES  (unsigned) 10240 // Maximum allocation size

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

static unsigned maxalloc;    // Maximum number of units allocated
static Header base;          // Empty list to get started
static Header *freep = NULL; // Start of free list

/*
 * free(): put block ap in free list
 */

void free(void *ap) {

    Header *bp;
    Header *p;

#ifdef DEBUG
    fprintf(stderr, "free(): freeing up allocated memory at %px\n", ap);
#endif

    // Bail of there is nothing to return
    if (ap == NULL)
        return;

    // Point to block header
    bp = (Header *)ap - 1;

    // Bail out if being requested to free up too much or nothing
    if (bp->s.size == 0 || bp->s.size > maxalloc) {
        fprintf(stderr, "free(): cannot free requested units\n");
        return;
    }

    //
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

    up         = (Header *)cp;
    up->s.size = nu;
    maxalloc   = (up->s.size > maxalloc) ? up->s.size : maxalloc;

    free((void *)(up + 1));

    return freep;
}

/*
 * malloc(): general-purpose storage allocator
 */

void *malloc(unsigned long nbytes) {

    Header *p;
    Header *prevp;
    unsigned long nunits;

#ifdef DEBUG
    fprintf(stderr, "malloc(): allocating %lu bytes\n", nbytes);
#endif

    // Guard against requesting too much space
    if (nbytes > MAXBYTES) {
        fprintf(stderr, "malloc(): cannot allocate requested size in bytes\n");
        return NULL;
    }

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
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
    char     *p;
    char     *q;

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

/*
 * bfree(): free an arbitrary bock p of n characters
 */

unsigned long bfree(char *p, unsigned long n) {

    Header *hp;

#ifdef DEBUG
    fprintf(stderr, "bfree(): attempting to free block at %px of %lu bytes\n", p, n);
#endif

    if (n < sizeof(Header))
        return 0;

    hp         = (Header *) p;
    hp->s.size = n / sizeof(Header);

    free((void *)(hp + 1));

    return hp->s.size;
}

/* Main */

int main(void) {

    void *memptr;
    unsigned long freed;

    fprintf(stderr, "%s\n", "hello");

    memptr = malloc(10);
    fprintf(stdout, "main(): memory allocated at %px\n", memptr);
    free(memptr);

    memptr = calloc(5, sizeof(double));
    fprintf(stdout, "main(): memory allocated at %px\n", memptr);
    free(memptr);

    // This next allocation should push us over the limit
    memptr = calloc(10, 128);
    fprintf(stdout, "main(): memory allocated at %px\n", memptr);
    free(memptr);

    // Test bfree()
    memptr = malloc(10000);
    freed = bfree(memptr, 1000);
    if (freed != 0)
        fprintf(stderr, "bfree() was successfully able to free an arbitrary block of size %lu\n", freed);
    else
        fprintf(stderr, "bfree() was not successful\n");

}
