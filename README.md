Worked Excercises from _The C Programming Language_, by Brian W. Kernignham and Dennis M. Ritchie
=======

This repository contains solutions to the examples presented in the classic book
[_The C Programming Language_](https://en.wikipedia.org/wiki/The_C_Programming_Language), by [Brian W. Kerningham](https://en.wikipedia.org/wiki/Brian_Kernighan) and [Dennis M. Ritchie](https://en.wikipedia.org/wiki/Dennis_Ritchie).  In many cases they
have been written to utilize [C99](https://en.wikipedia.org/wiki/C99) features. Solutions for any given chapter attempt to only use featured introduced up to that point in
the book.

Kernighan and Ritchie The C Programming Language Code Examples

### Cross-Platform Testing

So far, the code in this repository has only been complied and tested on Apple OS X El Capitan v10.11 using the clang compiler [Apple LLVM version 7.3.0 (clang-703.0.31)].  Additionally, I utilized the 'splint' linter (v3.1.2).  If you want to compile these without splint, the Makefiles will need to be modified accordingly.

### Chapter 1 - "A Tutorial Introduction"

* 1-01 - helloworld.c:  Hello World
* 1-02 - escapechars.c:  All escape characters
* 1-03 - ftoc.c:  Fahrenheit-Celsius
* 1-04 - ctof.c:  Celsius-Fahrenheit
* 1-05 - ftoc-reverse.c:  Fahrenheit-Celsius in Reverse
* 1-06 - eofvalue.c:  Determine the value of EOF returned by getchar() from stdin
* 1-07 - printeof.c:  Print the value of EOF directly
* 1-08 - countchar.c:  Count blanks, tabs, and new lines from stdin
* 1-09 - singleblank.c:  Replace one or more blanks with a single blank
* 1-10 - showhiddens.c:  Replaces tabs, backspaces, and backslashes by their escape characters
* 1-11 - countwords.c:  Counts the number of words
* 1-12 - wordperline.c:  Outputs its input one word per time
* 1-13 - wordhistohori.c:  Horizontally-oriented histogram of the number of words
*      - wordhistovert.c:  Vertically-oriented histogram of the number of words
* 1-14 - charhistohori.c:  Horizontally-oriented histogram of the number of characters
*      - charhistovert.c:  Vertically-oriented histogram of the number of characters
* 1-15 - ftoc-func.c:  Fahrenheit-Celsius Table (using a function)
* 1-16 - longestline.c:  Print arbitrarily long lines
* 1-17 - longlines.c:  Prints lines longer than 80 characters
* 1-18 - cleantrailsnblanks.c:  Cleans out trailing blanks and tabs. Eliminates blank lines.
* 1-19 - reverse.c:  Reverses all input one line at a time
* 1-20 - detab.c:  Replace tabs with blank spaces
* 1-21 - entab.c:  Replaces converts spaces to tabs according to tab stops
* 1-22 - fold.c:  Folds long lines to a specified width
* 1-23 - nocomment.c:  Removes all comments from a C program
* 1-24 - minilint.c:  Performs rudementary syntax checks on a C program

### Chapter 2 - "Types, Operators, and Expressions"

* 2-01 - typelimits.c:  Prints the ranges of each of the numeric types
* 2-02 - equivloop.c:  For-loop equivalent to longestline without using logical operators
* 2-03 - htoi.c:  Implements htoi() hexadecimal to integer converter
* 2-04 - squeeze.c:  Implements squeze() which removes multiple chars from a string
* 2-05 - any.c:  Implements any() which returns the position of a search char
* 2-06 - setbits.c:  Implements setbits() which sets bits based upon a pattern
* 2-07 - invert.c:  Implements invert() which inverts the bits starting at a position
* 2-08 - rightrot.c:  Implements rightrot() which returns the value of a rotated integer
* 2-09 - fastbitcount.c:  Implements a faster bitcount() using a two's complement property
* 2-10 - tolower.c:  Implements a lower() using a trinary conditional

### Chapter 3 - "Control Flow"

* 3-01 - binsearch.c:  Implements a binary search with only one test inside the main loop
* 3-02 - escape.c:  Tools to handle escape characters (bi-directionally)
* 3-03 - expand.c:  Expands regex style string ranges (e.g. 'a-z')
* 3-04 - itoa.c:  Version of itoa() that handles the largest negative integer
* 3-05 - itob.c:  Implements itob() that converst a number to a string of a particular base
* 3-06 - itoaw.c:  Implements itoaw() that cconvers number to string of a minimum width

### Chapter 4 - "Functions and Program Structure"

* 4-01 - strrindex.c:  Returns the position of the rightmost occurance of text in a string
* 4-02 - atof.c:  Implements atof() string to double converter with scientific notation support
* 4-03 - rpncalc4-03/  RPN Calculator supporting modulus and negative number support
* 4-04 - rpncalc4-04/  RPN Calculator (rpncalc2) extended to include stack inspection and manipulation
* 4-05 - rpncalc4-05/  RPN Calculator (rpncalc3) extended to support math functions
* 4-06 - rpncalc4-06/  RPN Calculator (rpncalc4) extended to support variables
* 4-07 - ungets.c:  Implements ungets() that returns a whole string to the input buffer
* 4-08 - singlegetch.c:  Implements getch() and ungetch() that support just a single char buffer
* 4-09 - ungetseof.c:  Implements getch(), ungetch(), and ungets() in a maner supporting EOF
* 4-10 - rpncalc4-10/  RPN Calculator (rpncalc5) based upon whole line handling
* 4-11 - rpncalc4-11/  RPN Calculator (rpncalc6) that uses 'static' to negate needing ungetch()
* 4-12 - itoarecursive.c:  A recursive implementation of itoa()
* 4-13 - reverserecursive.c:  A recursive implementation of reverse()
* 4-14 - swapmacro.c:  A version of reverse() that uses a macro for swaping two values

### Chapter 5 - "Pointers and Arrays"

* 5-01 - getint.c:  Implements getint() that returns an integer (w/limit checks)
* 5-02 - getfloat.c:  Implements getfloat() that returns a floating point
* 5-03 - strcat.c:  Implements pointer version of strcat()
* 5-04 - strend.c:  Implements strend() that returns true if one string is at the end of another
* 5-05 - strnfunc/  Implements library versions of library functions:
  * strncpy.c:  strncpy()
  * strncat.c:  strncat()
  * strncmp.c:  strncmp()
* 5-06 - pointers/  Implements a pointer version of:
  * anyp.c:  any()
  * atofp.c:  atof()
  * cleantrailsnblanksp.c:  cleantrailsnblanks()
  * escapep.c:  escape()
  * expandp.c:  expand()
  * htoip.c:  htoi()
  * itoawp.c:  itoaw()
  * itobp.c:  itob()
  * longestlinep.c:  longestline()
  * reversep.c:  reverse()
  * reverserecursivep.c:  reverserecursive()
  * squeezep.c:  squeeze()
* 5-07  Supports array of pointer exercise (plus qsort and rudimentary 'alloc()' tests
  * readline.c:  First version of readline that uses alloc() (c.f. section 5.6)
  * readline2.c:  Alternate version for exercise 5-07. Compare timings with 'readline.c'
* 5-08 - datetools.c:  Adds error checking to day_of_year() and month_day()
* 5-09 - datetoolsp.c:  Implements day_of_year() and month_day() using pointers, added month_name()
* 5-10 - expr/  Command line version of RPN Calculator ("expr")
* 5-11
  * detab2.c:  Replace tabs with blank spaces using a passed set of tab stops
  * entab2.c:  Replaces converts spaces to tabs according to tab stops using a passed set of tab stops
* 5-12
  * detab3.c:  Replace tabs with blank spaces using command switches to set intervals
  * entab3.c:  Replaces converts spaces to tabs using command switches to set intervals
* 5-13 - tail2.c:  Displays the specified number of lines from the end of a file
* 5-14 - sort1.c:  Sorts input lines supporting reverse and numeric ordering using '-r' and '-n' switches
* 5-15 - sort2.c:  Extends sort1.c to also support '-f' switch to fold upper and lower case
* 5-16 - sort3.c:  Extends sort2.c to also support '-d' switch to sort by 'directory order'
* 5-17 - sort4.c:  Extends sort3.c to also support for searching a fixed position field ('+pos1', '-pos1')
* 5-18 - dcl.c:  Parses a C language pointer declaration (with some error handling)
* 5-19 - undcl.c:  Converts (sort of) natural language into a C language pointer declaration
* 5-20 - dcl2.c:  Extends dcl.c to support function argument types, qualifiers like const, etc

### Chapter 6 - "Structures"

* 6-01 - getword.c:  Gets next key word or character handling underscore, string constants, comments, and preprocessor control lines
* 6-02 - getvars.c:  Prints variable names in a C program that are identical in the first 'X' characters (6 by default)
* 6-03 - wordxref.c:  Cross-references words from stdin by line number excluding stop words
* 6-04 - wordfreq.c:  Lists all the distinct words from stdin listed in decreasing frequency
* 6-05 - tablookup.c:  Implements a hash table based table look-up set of functions
* 6-06 - define.c:  Simple '#define' pre-processor

### Chapter 7 - "Input and Output"

* 7-01 - chngcase.c:  Transforms input to all upper or lower case based upon name of program ('lower' or 'upper')
* 7-02 - print.c:  Prints a file with arbitrary contents in a reasonable way
* 7-03 - minprintf.c:  Faux implementation of printf to demonstrate variable arguments
* 7-04 - minscanf.c:  Faux implementation of scanf to introduce scanf
* 7-05 - scancalc/  A variation of whole line RPN calc from 4-10 that utilizes sscanf
* 7-06 - mindiff.c:  Prints first line where two files differ
* 7-07 - minfind.c:  Searches files lines either matching, or not matching, a pattern optional line numbers
* 7-08 - fprint.c:  Prints a set of files with header, footer, page breaks, and page count

### Chapter 8 - "The UNIX System Interface"

* 8-01  A minimal impact of cat which concatinates files using low-level OS calls
  * mincat.c:  First version of mincat that uses low-level OS calls (c.f. sections 8.2, 8.3)
  * mincat2.c:  Alternate version for exercise 8-01 using stdio calls--compare timings with 'mincat.c'
* 8-02  A version of minimal stdio functions implemented with fields instead of bits. Compare timings and size with minstdiotest.c.
  * stdiobits.c:  Test program that excercises 'minstdio0'. Compare timings and size with 'minstdiotest.c'.   Execution time in ticks is returned as the exit status (view with 'echo $?' after running).
  * minstdio0.h:  Header for a minimal implementation of some 'stdio' library functions using bit fields
  * minstdio0.c:  Minimal implementation of some 'stdio' library functions using bit fields
* 8-03 Implements _flushbuf(), fflush(), and fclose().
  * minstdiotest.c:  Test program that excercises 'minstdio'. Execution time in ticks is returned as the exit status (view with 'echo $?' after running).
  * minstdio.h:  Header for a minimal implementation of some 'stdio' library functions bit functions
  * minstdio.c:  Minimal implementation of some 'stdio' library functions using bit functions
* 8-04 Implementation of fseek()
  * fseektest.c:  Test program that exercises fseek()
  * minstdio1.h:  Header for a minimal 'stdio' library that includes the addition of fseek()
  * minstdio1.c:  Minimal implementation of 'stdio' library inlcuding the addition of fseek()
* 8-05 - fileinfo.c:  Returns information (name, last modified, size) of files in a directory recursing down the directory chain
* 8-06 - calloc.c:  A minimal implimentation of malloc() and free() plus a version of calloc()
* 8-07 - calloc2.c:  Adds some error checking to malloc() routines
* 8-08 - bfree.c:  Adds bfree() to malloc()

##Extras

In many cases these are programs outlined in K&R which are useful or interesting but were not carried forward into an exercise. The other cases are test programs or experiments.

* echoargs.c:  Echos passed arguments
* getkeywords.c:  Implements getkeywords program from section 6.3
* makebigline.c:  Outputs a 3001 character text line
* points.c:  Implements 'points' examples from 6.1 and 6.2 of "structures" chapter
* porterstem.c:  Almost a straight port of Martin's implementation of Martin Porter's stemming algorithm with minor updates for coding styling, types (bool, size_t, char), comment expansion, partial splint compliance, big static buffer, etc.
* rpncalc/  Unadulterted (pre-exercise) RPN Calculator (rpncalc0)
* saveasascii.c:  Strips input of everything except regular values
* size.c:  Counts the number of characters in the input
* testupcase.c:  Tests a technique to convert uppercase ASCII letters to lowercase
* wordxrefstem.c:  An alternative implementation of wordxref.c (6-03) that leverages Martin Porter's stemming algorithm

##Test Files

The following test data files are provided to support manually testing the exercises. Specifically, the ones that draw from standard input can be manually tested with these.

* bigline.txt - One really big single line of text (3001 chars)
* bignegative.txt - A big (out of range) negative integer
* comment.txt - A C program containing test scenarios for 'nocomment.c' and 'getword.c'
* dcl.txt - Test file for 'dcl.c'
* dcl2.txt - Differs from 'dcl.c' slightly.  Good test file for 'mincomp.c'
* empty.txt - One empty line (just a '\n')
* extraspecials.txt - Contains embedded backspace, tabs, and backslashes
* huckfinn.txt - Project Gutenberg copy of Adventures of Huckleberry Finn by Mark Twain
* float.txt - A floater
* floatexp.txt - A float with exponent.
* integer.txt - An integer
* largestnegint.txt - Largest negative integer (per typelimits.c)
* largestposint.txt - Largest positive integer (per typelimits.c)
* linttest.txt - Test file for 'minilint.c'
* names.txt - Twenty (20) random names
* negativeint.txt - A negative integer (with some whitespace)
* notanum.txt - Not a number
* oneline.txt - One line of text but with no terminating newline ('\n')
* tabfun1.txt - Tab test file of diagonal 'x's using spaces and tabs assuming a tab spacing of 4
* tabfun2.txt - Tab test file of diagonal 'x's using spaces only
* tabs.txt - Basic tabs followed by 'x' chars
* test1.txt - Increasing number of characters per line with variations at the end
* words.txt - Some words used to test wordxref.c punctuation handling
* zero.txt - A totally empty file (no data)

##Style

See *[STYLE.md](https://github.com/ptdecker/cbasics/blob/master/STYLE.md)* for notes on overall style and approach to the code

##License

These solutions are copyright under the terms of the GNU GENERAL PUBLIC LICENSE v3 (see LICENSE) with the following exceptions:

* While not at all specified by the exercises, in the extras is included an implementation of the word cross-reference program from exercise 6-03 that also stems the words.  It utilizes an imlementation of a Porter stemmer created by Martin Porter. As stated on his web site, the implementations provided on his site are free of charge (freeware).

* Initially, I included an implementation of the 'strlen()' function in selected exercises, including but possibly not limited to: itoa.c, itoaw.c, and itob.c are highly based upon the P.J. Plauger's wonderful work "The Standard C Library".  As such, per the terms outlined in the preface of this work (p. xii), I include the following verbiage:  "Portions of this work are derived from The Standard C Library, copyright (c) 1992 by P.J. Plauger, published by Prentice-Hall, and are used with permission."  However, I have since modified these programs to use the strlen from the standard library.

* In addition, some of the solutions presented draw from Tondo and Gimpel's most helpful "The C Answer Book." In several cases, I worked out my own solutions then found better optimizations and cleaner ways of handling things based upon Tondo and Gimpel's work. This work is a bit dated and even in the places where their solutions were drawn from the code presented here has been updated closer to the c99 standard. In addition, many suggestions driven by the 'splint' linter have been incorporated causing further shift away from "The C Answer Book." THe Tondo and Gimple book I drew from has a copyright of 1989. I have not researched if it has been renewed or expired.

* Finally, by definition, the code presented here draws from, and directly answers the excercises presented within, Kernighan's and Ritchie's fundamental "The C Programing Language, 2nd Edition." This foundational work from 1988 (2nd edition) and 1978 (1st edition) remains to this day one of the best guides to the C language.
