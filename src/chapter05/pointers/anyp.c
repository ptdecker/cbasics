/*
 * anyp.c  (pointer based version of 'any.c')
 *
 * Returns the first location in a string where any character from another string occurs.
 * If none of the characters in the other string are found, it returns '-1'.
 */

#include <stdbool.h>
#include <stdio.h>

#define NOTFOUND -1

/*
 * any(): Returns the first location in string s[] where any of the characters in string c[]
 *        occur.  Returns -1 if no characters in c[] are found within s[]
 */

static int any(char *s, char *c) {
    char *sindex = s;
    while (*sindex != '\0') {
        char *cindex = c;
        while (*cindex != '\0')
            if (*sindex++ == *cindex++)
                return (int)(sindex - s - 1);
    }
    return NOTFOUND;
}

int main(void) {

    char string1[] = "This string contains a bunch of 's' characters";
    int  pos;
    int  i;

    pos = any(string1, "aeiou");
    printf("Locating the first lowercase vowel in the string:\n\n\"This string contains a bunch of 's' characters\"\n");
    if (pos != NOTFOUND) {
        (void)putchar(' ');
        for (i = 0; i < pos; i++)
            (void)putchar(' ');
       (void)putchar('^');
        printf("\n\nFound at position: %d (where '0' is the first character)\n\n", pos);
    } else
        printf("\n\nNot found!\n\n");

    pos = any(string1, "x");
    printf("Locating the character 'x' in the string:\n\n\"This string contains a bunch of 's' characters\"\n");
    if (pos != NOTFOUND) {
        (void)putchar(' ');
        for (i = 0; i < pos; i++)
            (void)putchar(' ');
       (void)putchar('^');
        printf("\n\nFound at position: %d (where '0' is the first character)\n\n", pos);
    } else
        printf("\n\nNot found!\n\n");

    return 0;
}
