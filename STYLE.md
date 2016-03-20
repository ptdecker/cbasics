Style and Approach Notes
===

* Per Plauger, _size_t_ is used as the type for all array index. Refere to Plauger p.219 for an excellent discussion as to why this is done as opposed to the _int_ type used in most examples from (K&R) and (T&G).

* _main(void)_ is always used when arguments passed to the program are not used. None of the primary reference sources [(K&R), (T&G), nor (Plauger)] use this practice, but it is good as an indicator that these are ignored.

* Similarly, functions that return a value which is subsequently ignored are also cast as type _void_ (cast into the void so to speak) to indicate that their return value is deliberately being ignored. This keeps splint happy too.

* The _bool_ type supported by the c99 standard library _stdbool.h_ is utilized for clarity.

* I try to make a clearer distinction between when I use _char_ vs _int_ even though during (K&R) times they were interchangable. I'm a bit loose about it and as such have _+charint_ enabled on *splint* so that it doesn't continually complain to me when I got lazy and tired of explicit type casing between the two.

* I love state machines so several of my solution approaches leverage them. One example is *minilint.c* in from chapter one. (T&G) does not go this route so my solutions to these exercises vary significantly from the ones offered by this source.

## Source

(K&R) "The C Programming Language, 2nd Edition", Brian W. Kernighan, Dennis M. Ritchie.
(Plauger) "The Standard C Library", P. J. Plauger
(T&G) "The C Answer Book", Clovis L. Tondo, Scott E. Gimpel