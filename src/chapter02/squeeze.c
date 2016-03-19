/*
 * squeeze.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * squeezechar(): Deletes all 'c' from S[]
 *
 * NOTE: squeezechar() is the version of squeeze() implemnted in 2.8 of K&R
 *       and squeeze() is ther alternate version suggested by the excercises.
 */

static void squeezechar(char s[], char c) {

    int i;
    int j;

    for (i = 0, j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}

/*
 * squeeze(): Deletes all characters contained in delete[] from s[]
 */

static void squeeze(char s[], char delete[]) {

    int i;
    int j;
    int k;
    bool keep;

    for (i = 0, j = 0; s[i] != '\0'; i++) {
        keep = true;
        for (k = 0; delete[k] != '\0' && keep; k++)
            keep = (s[i] != delete[k]);
        if (keep)
            s[j++] = s[i];
    }

    s[j] = '\0';
}




int main(void) {

    char string1[] = "This string contains a bunch of 's' characters";
    char string2[] = "This string contains a bunch of 's' characters";

    squeezechar(string1, 's');
    printf("Removing all 's' from \"This string contains a bunch of 's' characters\"\n\nResult: \"%s\"\n", string1);

    squeeze(string2, "aeiou");
    printf("\nNow, remvoing all lowercase vowels from \"This string contains a bunch of 's' characters\"\n\nResult: \"%s\"\n", string2);

    exit(EXIT_SUCCESS);
}
