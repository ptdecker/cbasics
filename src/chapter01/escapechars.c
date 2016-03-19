/*
 * Attempts to print escape characters not listed in chapter one
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("\\a: \a\n");
//    printf("\\b: \b\n"); // chapter one control character
    printf("\\c: \c\n");
    printf("\\d: \d\n");
    printf("\\e: \e\n");
    printf("\\f: \f\n");
    printf("\\g: \g\n");
    printf("\\h: \h\n");
    printf("\\i: \i\n");
    printf("\\j: \j\n");
    printf("\\k: \k\n");
    printf("\\l: \l\n");
    printf("\\m: \m\n");
//    printf("\\n: \n\n"); // chapter one control character
    printf("\\o: \o\n");
    printf("\\p: \p\n");
    printf("\\q: \q\n");
    printf("\\r: \r\n");
    printf("\\s: \s\n");
//    printf("\\t: \t\n"); // chapter one control character
//    printf("\\u: \u\n"); // causes a compiler error
    printf("\\v: \v\n");
    printf("\\w: \w\n");
//    printf("\\x: \x\n"); // causes a compiler error
    printf("\\y: \y\n");
    printf("\\z: \z\n");
    printf("\\0: \0\n");
    printf("\\1: \1\n");
    printf("\\2: \2\n");
    printf("\\3: \3\n");
    printf("\\4: \4\n");
    printf("\\5: \5\n");
    printf("\\6: \6\n");
    printf("\\7: \7\n");
    printf("\\8: \8\n");
    printf("\\9: \9\n");
    printf("\\A: \A\n");
    printf("\\B: \B\n");
    printf("\\C: \C\n");
    printf("\\D: \D\n");
    printf("\\E: \E\n");
    printf("\\F: \F\n");
    printf("\\G: \G\n");
    printf("\\H: \H\n");
    printf("\\I: \I\n");
    printf("\\J: \J\n");
    printf("\\K: \K\n");
    printf("\\L: \L\n");
    printf("\\M: \M\n");
    printf("\\N: \N\n");
    printf("\\O: \O\n");
    printf("\\P: \P\n");
    printf("\\Q: \Q\n");
    printf("\\R: \R\n");
    printf("\\S: \S\n");
    printf("\\T: \T\n");
//    printf("\\U: \U\n"); // causes a compiler error
    printf("\\V: \V\n");
    printf("\\W: \W\n");
    printf("\\X: \X\n");
    printf("\\Y: \Y\n");
    printf("\\Z: \Z\n");
    printf("\\~: \~\n");
    printf("\\`: \`\n");
    printf("\\!: \!\n");
    printf("\\@: \@\n");
    printf("\\#: \#\n");
    printf("\\$: \$\n");
//    printf("\\%: \%\n"); // causes a linter warning
    printf("\\^: \^\n");
    printf("\\&: \&\n");
    printf("\\*: \*\n");
    printf("\\(: \(\n");
    printf("\\): \)\n");
    printf("\\_: \_\n");
    printf("\\-: \-\n");
    printf("\\+: \+\n");
    printf("\\=: \=\n");
    printf("\\{: \{\n");
    printf("\\[: \[\n");
    printf("\\}: \}\n");
    printf("\\]: \]\n");
    printf("\\|: \|\n");
//    printf("\\\: \\\n"); // chapter one control character
    printf("\\:: \:\n");
    printf("\\;: \;\n");
//    printf("\\\": \"\n"); // chapter one control character
    printf("\\': \'\n");
    printf("\\<: \<\n");
    printf("\\,: \,\n");
    printf("\\>: \>\n");
    printf("\\.: \.\n");
    printf("\\?: \?\n");
    printf("\\/: \/\n");
    exit(EXIT_SUCCESS);
}
