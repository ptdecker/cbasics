// NOTE: For information on OS X (OS X 10.11.6) versions of <fcntl.h> and <unistd.h> see:
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/unistd.h
//           - http://opensource.apple.com/source/xnu/xnu-3248.60.10/bsd/sys/fcntl.h

// NOTE: For inforation on OSMalloc see:
//           - https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/KernelProgramming/vm/vm.html#//apple_ref/doc/uid/TP30000905-CH210-CHDHIIJF

#pragma clang diagnostic ignored "-Wdeprecated-declarations"	

#include <fcntl.h>
#include <unistd.h> // equivalent to (K&R) #include "syscalls.h"

#define NO_MEMORY (-1)
#define PAGE_SIZE_64K (64 * 1024)        // Page size to allocate

int main(void) {

	char *base    = NULL; // Memory buffer
	char *ptr     = base; // Location in buffer

	// Attempt to allocate PAGE_SIZE_? of memory
	if ((base = (char *)sbrk(PAGE_SIZE_64K)) == (char *)NO_MEMORY)
		return 1;
    ptr = base;

    // Stuff the buffer with stuff
	*ptr++ = 'f';
	*ptr++ = 'o';
	*ptr++ = 'o';
	*ptr++ = '\n';
	*ptr   = '\0';

	// Write it out to stdout
	(void)write(STDOUT_FILENO, base, (size_t)(ptr - base));

	// Free allocated memory
	(void)brk(base);

	// Get out of Dodge City, Kansas
	return 0;
}

/* Allocate
	OSMallocTag mytag = OSMalloc_Tagalloc(MINSTDIOTAG, OSMT_DEFAULT);
    if ((base = (char *)OSMalloc(PAGE_SIZE_64K, mytag)) == NULL)
    	return 1;
 */

/* Deallocate
	OSFree(base, PAGE_SIZE_64K, mytag);
 */