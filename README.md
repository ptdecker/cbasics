Worked Excercises from _The C Programming Language_, by Brian W. Kernignham and Dennis M. Ritchie
=======

This repository contains solutions to the examples presented in the classic book
[_The C Programming Language_](https://en.wikipedia.org/wiki/The_C_Programming_Language), by [Brian W. Kerningham](https://en.wikipedia.org/wiki/Brian_Kernighan) and [Dennis M. Ritchie](https://en.wikipedia.org/wiki/Dennis_Ritchie).  In many cases they
have been written to utilize [C99](https://en.wikipedia.org/wiki/C99) features. Solutions for any given chapter attempt to only use featured introduced up to that point in
the book.

Kernighan and Ritchie The C Programming Language Code Examples

### Chapter 1

* 1-01 - helloworld.c:         Hello World
* 1-02 - escapechars.c:        All escape characters
* 1-03 - ftoc.c:               Fahrenheit-Celsius
* 1-04 - ctof.c:               Celsius-Fahrenheit
* 1-05 - ftoc-reverse.c:       Fahrenheit-Celsius in Reverse
* 1-06 - eofvalue.c:           Determine the value of EOF returned by getchar() from stdin
* 1-07 - printeof.c:           Print the value of EOF directly
* 1-08 - countchar.c:          Count blanks, tabs, and new lines from stdin
* 1-09 - singleblank.c:        Replace one or more blanks with a single blank
* 1-10 - showhiddens.c:        Replaces tabs, backspaces, and backslashes by their escape characters
* 1-11 - countwords.c:         Counts the number of words
* 1-12 - wordperline.c:        Outputs its input one word per time
* 1-13 - wordhistohori.c:      Horizontally-oriented histogram of the number of words
*      - wordhistovert.c:      Vertically-oriented histogram of the number of words
* 1-14 - charhistohori.c:      Horizontally-oriented histogram of the number of characters
*      - charhistovert.c:      Vertically-oriented histogram of the number of characters
* 1-15 - ftoc-func.c:          Fahrenheit-Celsius Table (using a function)
* 1-16 - longestline.c:        Print arbitrarily long lines
* 1-17 - longlines.c:          Prints lines longer than 80 characters
* 1-18 - cleantrailsnblanks.c: Cleans out trailing blanks and tabs. Eliminates blank lines.
* 1-19 - reverse.c:            Reverses all input one line at a time
* 1-20 - detab.c:              Replace tabs with blank spaces
* 1-21 - entab.c:              Replaces converts spaces to tabs according to tab stops
* 1-22 - fold.c:               Folds long lines to a specified width
* 1-23 - nocomment.c:          Removes all comments from a C program
* 1-24 - minilint.c:           Performs rudementary syntax checks on a C program

### Chapter 2

* 2-01 - typelimits.c:         Prints the ranges of each of the numeric types
* 2-02 - equivloop.c:          For-loop equivalent withouth using logical operators
* 2-03 - htoi.c:               Implements htoi() hexadecimal to integer converter
* 2-04 - squeeze.c:            Implements squeze() which removes multiple chars from a string
* 2-05 - any.c:                Implements any() which returns the position of a search char


##Extras

* makebigline.c: Outputs a 3001 character text line
* testupcase.c:  Tests a technique to convert uppercase ASCII letters to lowercase
* saveasascii.c: Strips input of everything except regular values
* size.c:        Counts the number of characters in the input

##Test Files

The following test data files are provided to support testing the excercises:

* bigline.txt       - One really big single line of text (3001 chars)
* empty.txt         - One empty line (just a '\n')
* extraspecials.txt - Contains embedded backspace, tabs, and backslashes
* huckfinn.txt      - Project Gutenberg copy of Adventures of Huckleberry Finn by Mark Twain
* oneline.txt       - One line of text but with no terminating newline ('\n')
* test1.txt         - Increasing number of characters per line with variations at the end
* zero.txt          - A totally empty file (no data)
* extraspecials.txt - Contains extra spaces, backslashes, tabs, and backspace characters
* comment.txt       - A C program containing test scenarios for 'nocomment.c'
* linttest.txt      - Test file for 'minilint.c'
