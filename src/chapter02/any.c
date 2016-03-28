/*
 * any.c
 *
 * Returns the first location in a string where any character from another string occurs.
 * If none of the characters in the other string are found, it returns '-1'.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * any(): Returns the first location in string s[] where any of the characters in string c[]
 *        occur.  Returns -1 if no characters in c[] are found within s[]
 */

static int any(char s[], char c[]) {

    size_t i;
    size_t j;

    for (i = 0; s[i] != '\0'; i++)
        for (j = 0; c[j] != '\0'; j++)
            if (s[i] == c[j])
                return (int)i;

    return -1;
}

int main(void) {

    char string1[] = "This string contains a bunch of 's' characters";
    int  pos;
    int  i;

    pos = any(string1, "aeiou");
    printf("Locating the first lowercase vowel in the string:\n\n\"This string contains a bunch of 's' characters\"\n");
    if (pos > -1) {
        (void)putchar(' ');
        for (i = 0; i < pos; i++)
            (void)putchar(' ');
       (void)putchar('^');
        printf("\n\nFound at position: %d (where '0' is the first character)\n\n", pos);
    } else
        printf("\n\nNot found!\n\n");

    pos = any(string1, "x");
    printf("Locating the character 'x' in the string:\n\n\"This string contains a bunch of 's' characters\"\n");
    if (pos > -1) {
        (void)putchar(' ');
        for (i = 0; i < pos; i++)
            (void)putchar(' ');
       (void)putchar('^');
        printf("\n\nFound at position: %d (where '0' is the first character)\n\n", pos);
    } else
        printf("\n\nNot found!\n\n");

    exit(EXIT_SUCCESS);
}
