/* This is the Porter stemming algorithm, coded up in ANSI C by the
   author. It may be be regarded as canonical, in that it follows the
   algorithm presented in

   Porter, 1980, An algorithm for suffix stripping, Program, Vol. 14,
   no. 3, pp 130-137, only differing from it at the points marked
  --DEPARTURE-- below.

   See also http://www.tartarus.org/~martin/PorterStemmer

   The algorithm as described in the paper could be exactly replicated
   by adjusting the points of DEPARTURE, but this is barely necessary,
   because (a) the points of DEPARTURE are definitely improvements, and
   (b) no encoding of the Porter stemmer I have seen is anything like
   as exact as this version, even with the points of DEPARTURE!

   You can compile it on Unix with 'gcc -O3 -o stem stem.c' after which
   'stem' takes a list of inputs and sends the stemmed equivalent to
   stdout.

   The algorithm as encoded here is particularly fast.

   Release 1: was many years ago
   Release 2: 11 Apr 2013
       fixes a bug noted by Matt Patenaude <matt@mattpatenaude.com>,

       case 'o': if (ends("\03" "ion") && (b[j] == 's' || b[j] == 't')) break;
           ==>
       case 'o': if (ends("\03" "ion") && j >= k0 && (b[j] == 's' || b[j] == 't')) break;

       to avoid accessing b[k0-1] when the word in b is "ion".
   Release 3: 25 Mar 2014
       fixes a similar bug noted by Klemens Baum <klemensbaum@gmail.com>,
       that if step1ab leaves a one letter result (ied -> i, aing -> a etc),
       step2 and step4 access the byte before the first letter. So we skip
       steps after step1ab unless k > k0.
*/

#include <stdbool.h>
#include <string.h>  // for memmove
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFERSIZE 1024 // size of buffer

/* The main part of the stemming algorithm starts here. b is a buffer
   holding a word to be stemmed. The letters are in b[k0], b[k0+1] ...
   ending at b[k]. In fact k0 = 0 in this demo program. k is readjusted
   downwards as the stemming progresses. Zero termination [of strings]
   is not in fact used in the algorithm.

   Note that only lower case sequences are stemmed. Forcing to lower case
   should be done before stem(...) is called.
*/

static char   *b;   // buffer for word to be stemmed
static size_t  k;   // offset to last character in the buffer of the word to be stemmed
static size_t  k0;  // offset to first character in the buffer of the word to be stemmed
static size_t  j;   // j is a general offset into the string

/*
 * cons(): returns 'true' if b[i] is a consonant
 */

static bool cons(size_t i) {
    switch (b[i]) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return false;
        case 'y':
            // Handle the case where 'y' could be a vowel, i.e. it is either
            // the first character of the word to be stemmed or if the prior
            // character in the word is a vowel.
            return (i == k0) ? true : !cons(i - 1);
        default:
            return true;
    }
}

/* m() measures the number of consonant sequences between k0 and j. if c is
   a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
   presence,

      <c><v>       gives 0
      <c>vc<v>     gives 1
      <c>vcvc<v>   gives 2
      <c>vcvcvc<v> gives 3
      ....
*/

static size_t m() {

    size_t n = 0;
    size_t i = k0;

    while (true) {
        if (i > j)
            return n;
        if (! cons(i))
            break;
        i++;
    }
    i++;

    while (true) {
        while (true) {
            if (i > j)
                return n;
            if (cons(i))
                break;
            i++;
        }
        i++;

        n++;
        while (true) {
            if (i > j)
                return n;
            if (! cons(i))
                break;
            i++;
        }
        i++;
    }
}

/* vowelinstem() is TRUE <=> k0,...j contains a vowel */

static bool vowelinstem() {

    size_t i;

    for (i = k0; i <= j; i++)
        if (! cons(i))
            return true;
  
    return false;
}

/* doublec(j) is TRUE <=> j,(j-1) contain a double consonant. */

static bool doublec(size_t j) {

    if (j < k0+1)
        return false;

    if (b[j] != b[j-1])
        return false;

    return cons(j);
}

/* cvc(i) is TRUE <=> i-2,i-1,i has the form consonant - vowel - consonant
   and also if the second c is not w,x or y. this is used when trying to
   restore an e at the end of a short word. e.g.

      cav(e), lov(e), hop(e), crim(e), but
      snow, box, tray.

*/

static bool cvc(size_t i) {

    int ch;

    if (i < k0 + 2 || !cons(i) || cons(i - 1) || !cons(i - 2))
        return false;

    ch = b[i];
    if (ch == 'w' || ch == 'x' || ch == 'y')
        return false;
   
    return true;
}

/* ends(s) is TRUE <=> k0,...k ends with the string s. */

static bool ends(char *s) {

    size_t length = (size_t)s[0];

    if (s[length] != b[k])
        return false; /* tiny speed-up */

    if (length > k - k0 + 1)
        return false;

    if (memcmp(b + k - length + 1, s + 1, length) != 0)
        return false;

    j = (length > k) ? 0 : (k - length);

    return true;
}

/* setto(s) sets (j+1),...k to the characters in the string s, readjusting
   k. */

static void setto(char *s) {

    size_t length = (size_t)s[0];

    memmove(b + j + 1, s + 1, length);

    k = j + length;
}

/* r(s) is used further down. */

static void r(char *s) {

    if (m() > 0)
        setto(s);
}

/* step1ab() gets rid of plurals and -ed or -ing. e.g.

       caresses  ->  caress
       ponies    ->  poni
       ties      ->  ti
       caress    ->  caress
       cats      ->  cat

       feed      ->  feed
       agreed    ->  agree
       disabled  ->  disable

       matting   ->  mat
       mating    ->  mate
       meeting   ->  meet
       milling   ->  mill
       messing   ->  mess

       meetings  ->  meet

*/

static void step1ab() {

    char ch;

    if (b[k] == 's') {
        if (ends("\04" "sses"))
            k -= 2;
        else if (ends("\03" "ies"))
            setto("\01" "i");
        else if (b[k-1] != 's')
            k--;
    }

    if (ends("\03" "eed")) {
        if (m() > 0)
            k--;
    } else if ((ends("\02" "ed") || ends("\03" "ing")) && vowelinstem()) {
        k = j;
        if (ends("\02" "at"))
            setto("\03" "ate");
        else if (ends("\02" "bl"))
            setto("\03" "ble");
        else if (ends("\02" "iz"))
            setto("\03" "ize");
        else if (doublec(k)) {
            k--;
            ch = b[k];
            if (ch == 'l' || ch == 's' || ch == 'z')
                k++;
        } else if (m() == 1 && cvc(k))
            setto("\01" "e");
    }
}

/* step1c() turns terminal y to i when there is another vowel in the stem. */

static void step1c() {

//    fprintf(stderr, "1c");

    if (ends("\01" "y") && vowelinstem())
        b[k] = 'i';
}


/* step2() maps double suffices to single ones. so -ization ( = -ize plus
   -ation) maps to -ize etc. note that the string before the suffix must give
   m() > 0. */

static void step2() {

    switch (b[k - 1]) {

        case 'a':
            if (ends("\07" "ational")) {
                r("\03" "ate");
                break;
            }
            if (ends("\06" "tional")) {
                r("\04" "tion");
                break;
            }
            break;

        case 'c':
            if (ends("\04" "enci")) {
                r("\04" "ence");
                break;
            }
            if (ends("\04" "anci")) {
                r("\04" "ance");
                break;
            }
            break;

        case 'e':
            if (ends("\04" "izer")) {
                r("\03" "ize");
                break;
            }
            break;

        case 'l':
            if (ends("\03" "bli")) {
                r("\03" "ble");
                break;
            }

// DEPARTURE: To match the published algorithm, replace the above if clause with
//          if (ends("\04" "abli")) {
//              r("\04" "able");
//              break;
//           }

            if (ends("\04" "alli")) {
                r("\02" "al");
                break;
            }
            if (ends("\05" "entli")) {
                r("\03" "ent");
                break;
            }
            if (ends("\03" "eli")) {
                r("\01" "e");
                break;
            }
            if (ends("\05" "ousli")) {
                r("\03" "ous");
                break;
            }
            break;

        case 'o':
            if (ends("\07" "ization")) {
                r("\03" "ize");
                break;
            }
            if (ends("\05" "ation")) {
                r("\03" "ate");
                break;
            }
            if (ends("\04" "ator")) {
                r("\03" "ate");
                break;
            }
            break;

        case 's':
            if (ends("\05" "alism")) {
                r("\02" "al");
                break;
            }
            if (ends("\07" "iveness")) {
                r("\03" "ive");
                break;
            }
            if (ends("\07" "fulness")) {
                r("\03" "ful");
                break;
            }
            if (ends("\07" "ousness")) {
                r("\03" "ous");
                break;
            }
            break;

        case 't':
            if (ends("\05" "aliti")) {
                r("\02" "al");
                break;
            }
            if (ends("\05" "iviti")) {
                r("\03" "ive");
                break;
            }
            if (ends("\06" "biliti")) {
                r("\03" "ble");
                break;
            }
            break;

// DEPARTURE: To match the published algorithm, delete this next case statement

        case 'g':
            if (ends("\04" "logi")) {
               r("\03" "log");
               break;
            }

    }
}

/* step3() deals with -ic-, -full, -ness etc. similar strategy to step2. */

static void step3() {

    switch (b[k]) {

        case 'e':
            if (ends("\05" "icate")) {
                r("\02" "ic");
                break;
            }
            if (ends("\05" "ative")) {
                r("\00" "");
                break;
            }
            if (ends("\05" "alize")) {
                r("\02" "al");
                break;
            }
            break;

        case 'i':
            if (ends("\05" "iciti")) {
                r("\02" "ic");
                break;
            }
            break;

        case 'l':
            if (ends("\04" "ical")) {
                r("\02" "ic");
                break;
            }
            if (ends("\03" "ful")) {
                r("\00" "");
                break;
            }
            break;

        case 's':
            if (ends("\04" "ness")) {
                r("\00" "");
                break;
            }
            break;
    }
}

/* step4() takes off -ant, -ence etc., in context <c>vcvc<v>. */

static void step4() {

    switch (b[k-1]) {

        case 'a':
            if (ends("\02" "al"))
                break;
            return;

        case 'c':
            if (ends("\04" "ance"))
                break;
            if (ends("\04" "ence"))
                break;
            return;

        case 'e':
            if (ends("\02" "er"))
                break;
            return;

        case 'i':
            if (ends("\02" "ic"))
                break;
            return;

        case 'l':
            if (ends("\04" "able"))
                break;
            if (ends("\04" "ible"))
                break;
            return;

        case 'n':
            if (ends("\03" "ant"))
                break;
            if (ends("\05" "ement"))
                break;
            if (ends("\04" "ment"))
                break;
            if (ends("\03" "ent"))
                break;
            return;

        case 'o':
            if (ends("\03" "ion") && j >= k0 && (b[j] == 's' || b[j] == 't'))
                break;
            if (ends("\02" "ou")) // Takes care of -ous
                break;
            return;

        case 's':
            if (ends("\03" "ism"))
                break;
            return;

        case 't':
            if (ends("\03" "ate"))
                break;
            if (ends("\03" "iti"))
                break;
            return;

        case 'u':
            if (ends("\03" "ous"))
                break;
            return;

        case 'v':
            if (ends("\03" "ive"))
                break;
            return;

        case 'z':
            if (ends("\03" "ize"))
                break;
            return;

        default:
            return;
    }

    if (m() > 1)
        k = j;
}

/* step5() removes a final -e if m() > 1, and changes -ll to -l if
   m() > 1. */

static void step5() {

    size_t a;

    j = k;

    if (b[k] == 'e') {
      a = m();
      if (a > 1 || (a == 1 && !cvc(k - 1)))
          k--;
    }

    if (b[k] == 'l' && doublec(k) && m() > 1)
      k--;
}

/* In stem(p,i,j), p is a char pointer, and the string to be stemmed is from
   p[i] to p[j] inclusive. Typically i is zero and j is the offset to the last
   character of a string, (p[j+1] == '\0'). The stemmer adjusts the
   characters p[i] ... p[j] and returns the new end-point of the string, k.
   Stemming never increases word length, so i <= k <= j. To turn the stemmer
   into a module, declare 'stem' as extern, and delete the remainder of this
   file.
*/

static size_t stem(char *p, size_t i, size_t j) {

    b  = p;
    k  = j;
    k0 = i; /* copy the parameters into statics */

    /*
     * DEPARTURE: This next 'if' statement prevents strings of length 1 or 2 from
     * going through the stemming process, although no mention is made of this in the
     * published algorithm. Remove the line to match the publishedalgorithm.
     */

    if (k <= k0 + 1)
        return k;

    step1ab();
    if (k > k0) {
        step1c();
        step2();
        step3();
        step4();
        step5();
    }

    return k;
}

/*--------------------stemmer definition ends here------------------------*/

static void stemfile(FILE *f) {

    char   *s; // a char * (=string) pointer; passed into b above
    char   ch;
    size_t i;

    s = (char *)malloc(BUFFERSIZE);
    if (s == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(f)) != EOF) {

        if (!isalpha(ch)) {
            (void)putchar(ch);
            continue;
        }

        i = 0;
        while (true) {
            if (i == BUFFERSIZE) {
                fprintf(stderr, "error: out of buffer space\n");
                exit(EXIT_FAILURE);
            }
            s[i++] = tolower(ch);
            ch = getc(f);
            if (!isalpha(ch)) {
                (void)ungetc(ch,f);
                break;
            }
        }
        s[i] = '\0';
        
        s[stem(s, 0, i - 1) + 1] = '\0'; // Call stemmer then zero terminate string
        printf("%s",s);

    }

    free((void *)s);
}

int main(int argc, char *argv[]) {

    int i;

    for (i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i],"r");
        if (f == NULL) {
            fprintf(stderr,"File %s not found\n",argv[i]);
            exit(EXIT_FAILURE);
        }
        stemfile(f);
    }

    return 0;
}