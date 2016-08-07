/*
 * squeeze.c
 *
 * Pointer version
 */

#include <stdbool.h>
#include <stdio.h>

/*
 * squeezechar(): Deletes all 'c' from S[]
 *
 * NOTE: squeezechar() is the version of squeeze() implemnted in 2.8 of K&R
 *       and squeeze() is ther alternate version suggested by the excercises.
 */

static void squeezechar(char *s, char c) {

    char *squeezed = s;

    for ( ; *s != '\0'; s++)
        if (*s != c)
            *squeezed++ = *s;

    *squeezed = '\0';
}

/*
 * squeeze(): Deletes all characters contained in delete[] from s[]
 */

static void squeeze(char *s, char *delete) {

    char *squeezed  = s;

    for ( ; *s != '\0'; s++) {
        char *deletendx = delete;
        bool  keep;
        for (keep = true, deletendx = delete; *deletendx != '\0' && keep; deletendx++)
            keep = (*s != *deletendx);
        if (keep)
            *squeezed++ = *s;
    }

    *squeezed = '\0';
}




int main(void) {

    char string1[] = "This string contains a bunch of 's' characters";
    char string2[] = "This string contains a bunch of 's' characters";

    squeezechar(string1, 's');
    printf("Removing all 's' from \"This string contains a bunch of 's' characters\"\n\nResult: \"%s\"\n", string1);

    squeeze(string2, "aeiou");
    printf("\nNow, remvoing all lowercase vowels from \"This string contains a bunch of 's' characters\"\n\nResult: \"%s\"\n", string2);

    return 0;
}
