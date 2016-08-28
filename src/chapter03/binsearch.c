/*
 * binsearch.c: Binary search of an array with only one test inside the loop
 *
 * Sources:
 *  - https://en.wikipedia.org/wiki/Binary_search_algorithm
 *  - http://googleresearch.blogspot.com/2006/06/extra-extra-read-all-about-it-nearly.html
 */

// Includes

#include <stdio.h>

// Definitions

#define KEY_NOT_FOUND EOF

/*
 * binary_search(): search an array with binary search algorithm
 */

static int binary_search(int x, int v[], size_t n) {

    size_t low  = 0;
    size_t high = n - 1;

    while (low < high) {
        size_t mid = (low + high) >> 1;
        if (v[mid] < x)
            low  = mid + 1;
        else
            high = mid;
    }

    return ((high == low) && (v[low] == x)) ? (int)low : KEY_NOT_FOUND;
}

/* Main */

int main(void) {

    int    sorted[] = {13, 24, 34, 46, 52, 63, 77, 89, 91, 100};
    size_t len = 10;
    size_t index;
    int    key;

    printf("Array: ");
    for (index = 0; index < len; index++)
        printf("%d%s", sorted[index], ((index + 1) == len) ? "." : ", ");
    (void)putchar('\n');

    key = 46;
    printf("Key '%d' was found in position '%d'\n", key, binary_search(key, sorted, len));

    key = 10;
    printf("Key '%d' was found in position '%d'\n", key, binary_search(key, sorted, len));

    key = 100;
    printf("Key '%d' was found in position '%d'\n", key, binary_search(key, sorted, len));

    key = 110;
    printf("Key '%d' was found in position '%d'\n", key, binary_search(key, sorted, len));

    return 0;
}
