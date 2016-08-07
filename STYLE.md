Style and Approach Notes
===

* The vast majority of these exercise solutions do not represent safe coding practicies with respect to buffer overflow protection. Most string operations are open ended. The solutions were kept this way to be consistent with the K&R lessons but proper considerations should be made towards fixing this before usage in production systems.

* Per Plauger, _size_t_ is used as the type for all array index. Refere to Plauger p.219 for an excellent discussion as to why this is done as opposed to the _int_ type used in most examples from (K&R) and (T&G).

* _main(void)_ is always used when arguments passed to the program are not used. None of the primary reference sources [(K&R), (T&G), nor (Plauger)] use this practice, but it is good as an indicator that these are ignored.

* Similarly, functions that return a value which is subsequently ignored are also cast as type _void_ (cast into the void so to speak) to indicate that their return value is deliberately being ignored. This keeps splint happy too.

* The _bool_ type supported by the c99 standard library _stdbool.h_ is utilized for clarity.  K&R represents boolean values as either integers (0 for 'false') or an enumeration where the false value ("FALSE" or "NO") is zero so that conditionals that test for a boolean value work out.

* I try to make a clearer distinction between when I use _char_ vs _int_ even though during (K&R) times they were interchangable. I'm a bit loose about it and as such have _+charint_ enabled on *splint* so that it doesn't continually complain to me when I got lazy and tired of explicit type casing between the two.

* I love state machines so several of my solution approaches leverage them. One example is *minilint.c* in from chapter one. (T&G) does not go this route so my solutions to these exercises vary significantly from the ones offered by this source.

* I prefer using the "is" prefix for functions that return a boolean after performing a logic test, e.g. "isleap()" for testing if an integer representing a year is a leap year or not.  K&R does not use this style.  To keep consistency with the book, I retained the function name 'ptinrect' in points.c as opposed to "isptinrect" which I would have preferred.

* Following Plauger's advice, standard library #includes are ordered alphabetically.

* 'exit()' is used to terminate 'main()' only when file operations are used.  Otherwise, 'return' is utilized.  This avoids the extra overhead performed by exit (attempting to run atexit funcitons, and closing files) and it avoids the inclusion of <stdlib.h> when otherwise not needed. Note that the situation is a bit differnt in C++, c.f. http://stackoverflow.com/questions/461449/return-statement-vs-exit-in-main. 'exit()' is also used to terminate on hard failures outside of 'main()'. See also (K&R) pp. 26, 164.

## Source

(K&R) "The C Programming Language, 2nd Edition", Brian W. Kernighan, Dennis M. Ritchie.
(Plauger) "The Standard C Library", P. J. Plauger
(T&G) "The C Answer Book", Clovis L. Tondo, Scott E. Gimpel