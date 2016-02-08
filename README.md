cbasics
=======

Kernighan and Ritchie The C Programming Language Code Examples

1-01 - helloworld.c:         Hello World
1-02 - n/a
1-03 - ftoc.c:               Fahrenheit-Celsius
1-04 - ctof.c:               Celsius-Fahrenheit
1-05 - ftoc-reverse.c:       Fahrenheit-Celsius in Reverse
1-06 - eofvalue.c:           Determine the value of EOF returned by getchar() from stdin
1-07 - printeof.c:           Print the value of EOF directly
1-08 - countchar.c:          Count blanks, tabs, and new lines from stdin
1-09 - singleblank.c:        Replace one or more blanks with a single blank
1-10 - showhiddens.c:        Replaces tabs, backspaces, and backslashes by their escape characters
1-11 - countwords.c:         Counts the number of words
1-12 - wordperline.c:        Outputs its input one word per time
1-13 - wordhistohori.c:      Horizontally-oriented histogram of the number of words
     - wordhistovert.c:      Vertically-oriented histogram of the number of words
1-14 - charhistohori.c:      Horizontally-oriented histogram of the number of characters
     - charhistovert.c:      Vertically-oriented histogram of the number of characters
1-15 - ftoc-func.c:          Fahrenheit-Celsius Table (using a function)
1-16 - longestline.c:        Print arbitrarily long lines
1-17 - longlines.c:          Prints lines longer than 80 characters
1-18 - cleantrailsnblanks.c: Cleans out trailing blanks and tabs. Eliminates blank lines.

##Extras

makebigline.c:  Outputs a 3001 character text line
testupcase.c:   Tests a technique to convert uppercase ASCII letters to lowercase

##Test Files

The following test data files are provided:

bigline.txt       - One really big single line of text (3001 chars)
empty.txt         - One empty line (just a '\n')
huckfinn.txt      - Project Gutenberg copy of Adventures of Huckleberry Finn by Mark Twain
oneline.txt       - One line of text but with no terminating newline ('\n')
test1.txt         - Increasing number of characters per line with variations at the end
zero.txt          - A totally empty file (no data)
extraspecials.txt - Contains extra spaces, backslashes, tabs, and backspace characters
