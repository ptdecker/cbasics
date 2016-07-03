Index of Functions and Macros
=============================

Provides a index of all the functions and macros implemented in one form or another by these exercises. The number in brackets indicates chapter number associated with the exercise that implemented the designated function or macro ('[-]' indicates extras not specifically called out as exercises).  When multiple implementations are implemented for a function, in some cases the implementation may vary where the chapters illustrated new concepts implemented in the fuction and macro.  As such, the last implementation (with the exception of extras indicated by [-]) usually represents the most advanced implementation of the function or macro.  For some functions, more than one signature is listed.  This occurs in the case where pointer-based versions of the signatures were illustrated later and the two signatures are equivalent.  If the signatures are not equivalent, the implmentations are listed separately.

The routines leveraged by Martin Porter's stemmer in extras/porterstem.c and extras/wordxrefstem.c are not included in this index since they are strictly in support of his algorithm and not really a part of the K&R exercises body of work.

--- START OF INDEX ---

void addline(struct tnode *p, int linenum);
	[6] wordxref.c
	[-] wordxrefstem.c

struct point addpoint(struct point p1, const struct point p2);
	[-] points.c

void addword(struct tnode *p, char *uw);
	[-] wordxrefstem.c

char *alloc(int n);
	[5] readline.c
	[5] sort1.c
	[5] sort2.c
	[5] sort3.c
	[5] sort4.c

int any(char s[], char c[]);
int any(char *s,  char *c);
	[2] any.c
	[5] pointers/anyp.c

int anychar(char *s, char c);
	[6] getvars.c

int binary_search(int x, int v[], size_t n);
	[3] binsearch.c

struct key *binsearch(char *word, struct key tab[], size_t n)
	[6] getvars.c
	[-] getkeywords.c

unsigned bitcount(int x);
	[2] fastbitcount.c

bool caempty(void);
	[4] rpncalc4-03/castack.c
	[4] rpncalc4-04/castack.c
	[4] rpncalc4-05/castack.c
	[4] rpncalc4-06/castack.c
	[5] expr/castack.c
	[-] rpncalc/castack.c

static struct rect canonrect(const struct rect r);
	[-] points.c

char capop(void);
	[4] rpncalc4-03/castack.c
	[4] rpncalc4-04/castack.c
	[4] rpncalc4-05/castack.c
	[4] rpncalc4-06/castack.c
	[5] expr/castack.c
	[-] rpncalc/castack.c

void capush(char val);
	[4] rpncalc4-03/castack.c
	[4] rpncalc4-04/castack.c
	[4] rpncalc4-05/castack.c
	[4] rpncalc4-06/castack.c
	[5] expr/castack.c
	[-] rpncalc/castack.c

size_t casize(void);
	[4] rpncalc4-03/castack.c
	[4] rpncalc4-04/castack.c
	[4] rpncalc4-05/castack.c
	[4] rpncalc4-06/castack.c
	[5] expr/castack.c
	[-] rpncalc/castack.c

char comment(void);
	[6] define.c
	[6] getvars.c
	[6] getword.c
	[-] getkeywords.c

int compare(char *s, struct tnode *p, int num, bool *found);
	[6] getvars.c

void copy(char to[], char from[]);
void copy(char *to,  char *from);
	[1] longestline.c
	[2] equivloop.c
	[5] pointers/longestlinep.c

void daclear(void);
	[4] rpncalc4-04/dastack.c
	[4] rpncalc4-05/dastack.c
	[4] rpncalc4-06/dastack.c
	[4] rpncalc4-10/dastack.c
	[4] rpncalc4-11/dastack.c

void dadup(void);
	[4] rpncalc4-04/dastack.c
	[4] rpncalc4-05/dastack.c
	[4] rpncalc4-06/dastack.c
	[4] rpncalc4-10/dastack.c
	[4] rpncalc4-11/dastack.c

void dalist(void);
	[4] rpncalc4-04/dastack.c
	[4] rpncalc4-05/dastack.c
	[4] rpncalc4-06/dastack.c
	[4] rpncalc4-10/dastack.c
	[4] rpncalc4-11/dastack.c

double dapeek(void);
	[4] rpncalc4-04/dastack.c
	[4] rpncalc4-05/dastack.c
	[4] rpncalc4-06/dastack.c
	[4] rpncalc4-10/dastack.c
	[4] rpncalc4-11/dastack.c
	[5] expr/dastack.c

double dapop(void)
	[4] rpncalc4-03/dastack.c
	[4] rpncalc4-04/dastack.c
	[4] rpncalc4-05/dastack.c
	[4] rpncalc4-06/dastack.c
	[4] rpncalc4-10/dastack.c
	[4] rpncalc4-11/dastack.c
	[5] expr/dastack.c
	[-] rpncalc/dastack.c

void dapush(double val);
	[4] rpncalc4-03/dastack.c
	[4] rpncalc4-04/dastack.c
	[4] rpncalc4-05/dastack.c
	[4] rpncalc4-06/dastack.c
	[4] rpncalc4-10/dastack.c
	[4] rpncalc4-11/dastack.c
	[5] expr/dastack.c
	[-] rpncalc/dastack.c

size_t dasize(void);
	[4] rpncalc4-04/dastack.c
	[4] rpncalc4-05/dastack.c
	[4] rpncalc4-06/dastack.c
	[4] rpncalc4-10/dastack.c
	[4] rpncalc4-11/dastack.c

void daswap(void);
	[4] rpncalc4-04/dastack.c
	[4] rpncalc4-05/dastack.c
	[4] rpncalc4-06/dastack.c
	[4] rpncalc4-10/dastack.c
	[4] rpncalc4-11/dastack.c

int day_of_year(int year, int month, int day);
	[5] datetools.c
	[5] datetoolsp.c

void dcl(void);
	[5] dcl.c
	[5] dcl2.c

void dclspec(void);
	[5] dcl2.c

void detab(char *tabstop);
	[5] detab2.c
	[5] detab3.c

void dirdcl(void);
	[5] dcl.c
	[5] dcl2.c

void eatchar(void);
	[1] minilint.c
	[1] nocomment.c

void entab(char *tab);
	[5] entab2.c
	[5] entab3.c

void error(char *s);
	[5] sort4.c
	[5] tail2.c

void error(int c, char *s);
	[6] define.c

void errmsg(char *msg);
	[5] dcl.c
	[5] dcl2.c
	[5] undcl.c

void escape(char source[], char target[]);
void escape(char *source,  char *target);
	[3] escape.c
	[5] pointers/escapep.c

void expand(char source[], char target[]);
void expand(char *source,  char *target);
	[3] expand.c
	[5] pointers/expandp.c

size_t expandtab(size_t pos);
	[1] fold.c

size_t findblank(size_t pos);
	[1] fold.c

int foldcmp(const char *s, const char *t);
	[5] sort2.c
	[5] sort3.c
	[5] sort4.c

int folddircmp(const char *s, const char *t) 
	[5] sort3.c
	[5] sort4.c

int ftoc(int ftemp);
	[1] ftoc-func.c

char getch(void);
	[4] rpncalc4-03/lexer.c
	[4] rpncalc4-04/lexer.c
	[4] rpncalc4-05/lexer.c
	[4] rpncalc4-06/lexer.c
	[4] singlegetch.c
	[4] ungets.c
	[4] ungetseof.c
	[5] dcl.c
	[5] dcl2.c
	[5] expr/lexer.c
	[5] getfloat.c
	[5] getint.c
	[5] undcl.c
	[6] define.c
	[6] getvars.c
	[6] getword.c
	[6] wordfreq.c
	[6] wordxref.c
	[-] rpncalc/lexer.c
	[-] getkeywords.c
	[-] wordxrefstem.c

void getdef(void);
	[6] define.c

int getdouble(double *pn);
	[5] getfloat.c

int getint(int *pn);
	[5] getint.c

size_t getline(char s[], size_t lim);
size_t getline(char  *s, size_t lim);
	[1] cleantrailsnblanks.c
	[1] longestline.c
	[1] longlines.c
	[1] reverse.c
	[2] equivloop.c
	[4] rpncalc4-10/lexer.c
	[4] reverserecursive.c
	[4] swapmacro.c
	[5] pointers/cleantrailsnblanksp.c
	[5] pointers/longestlinep.c
	[5] pointers/reversep.c
	[5] pointers/reverserecursivep.c
	[5] readline.c
	[5] readline2.c
	[5] sort1.c
	[5] sort2.c
	[5] sort3.c
	[5] sort4.c
	[5] tail2.c

char getop(char s[]);
	[4] rpncalc4-03/lexer.c
	[4] rpncalc4-04/lexer.c
	[4] rpncalc4-05/lexer.c
	[4] rpncalc4-06/lexer.c
	[4] rpncalc4-10/lexer.c
	[4] rpncalc4-11/lexer.c
	[5] expr/lexer.c
	[-] rpncalc/lexer.c

int gettoken(void);
	[5] dcl.c
	[5] dcl2.c
	[5] undcl.c

char getword(char *word, int lim);
	[6] define.c
	[6] getword.c
	[6] getvars.c
	[6] wordfreq.c
	[6] wordxref.c
	[-] getkeywords.c
	[-] wordxrefstem.c

unsigned hash(char *s);
	[6] define.c
	[6] tablookup.c

unsigned int htoi(char s[]);
unsigned int htoi(char *s);
	[2] htoi.c
	[5] pointers/htoip.c

struct nlist *install(char *name, char *defn);
	[6] define.c
	[6] tablookup.c

unsigned invert(unsigned x, unsigned  p, unsigned n);
	[2] invert.c

bool isleap(int year);
	[5] datetools.c
	[5] datetoolsp.c

bool isnotstopword(char *w);
	[6] wordxref.c
	[-] wordxrefstem.c

bool isnottab(int pos, char *tabstop);
	[5] detab2.c
	[5] detab3.c
	[5] entab2.c
	[5] entab3.c

void itoa(int n, char s[]);
	[3] itoa.c
	[4] itoarecursive.c

void itoa(int n, char s[], int w);
void itoa(int n, char *s, int w);
	[3] itoaw.c
	[5] pointers/itoawp.c

void itob(int n, char s[], int b);
void itob(int n, char *s, int b);
	[3] itob.c
	[5] pointers/itobp.c

struct linklist *lalloc(void);
	[6] wordxref.c
	[-] wordxrefstem.c

struct linkwords *lwalloc(void);
	[-] wordxrefstem.c

void listprint(void)
	[6] wordfreq.c

void listsort(void);
	[6] wordfreq.c

void listsort(struct linkwords *head, int num_nodes)
	[-] wordxrefstem.c

void liststore(struct tnode *p);
	[6] wordfreq.c

struct nlist *lookup(char *s);
	[6] tablookup.c

char lower(char c);
	[2] lower.c

static void lowerstr(char *s);
	[6] wordfreq.c
	[6] wordxref.c
	[-] wordxrefstem.c

struct point makepoint(const int x, const int y);
	[-] points.c

void mathfun(char s[]);
	[4] rpncacl4-05/rpncalc3.c
	[4] rpncacl4-06/rpncalc4.c
	[4] rpncacl4-10/rpncalc5.c
	[4] rpncacl4-11/rpncalc6.c

#define max(a, b)
	[-] points.c

#define min(a, b)
	[-] points.c

void month_day(int year, int yearday, int *pmonth, int *pday);
	[5] datetoolsp.c
	[5] datetools.c

void *month_name(int month);
	[5] datetools.c

double myatof(char s[]);
double myatof(char *s);
	[4] atof.c
	[5] pointers/atofp.c

char *mystrdup(char *s);
	[6] define.c
	[6] getvars.c
	[6] tablookup.c
	[6] wordfreq.c
	[6] wordxref.c
	[-] wordxrefstem.c

void myqsort(char *v[], int left, int right);
	[5] readline.c
	[5] readline2.c

void myqsort(void *v[], int left, int right, int (*comp)(void *, void *))
	[5] sort1.c
	[5] sort2.c
	[5] sort3.c
	[5] sort4.c

int nexttoken(void);
	[5] undcl.c

int numcmp(char *s1, char *s2);
	[5] sort1.c
	[5] sort2.c
	[5] sort3.c
	[5] sort4.c

double origindist(const struct point pt);
	[-] points.c

void parmdcl(void);
	[5] dcl2.c

char peekch();
	[6] define.c

void printbits(unsigned x);
	[2] fastbitcount.c
	[2] invert.c
	[2] rightrot.c
	[2] setbits.c

void printline(size_t pos);
	[1] fold.c

bool ptinrect(const struct point p, struct rect r);
	[-] points.c

void readargs(int argc, char *argv[]);
	[5] sort4.c

int readlines(char *lineptr[], int maxlines);
	[5] readline.c
	[5] readline2.c
	[5] sort1.c
	[5] sort2.c
	[5] sort3.c
	[5] sort4.c

void reverse(char s[]);
void reverse(char *s);
	[1] reverse.c
	[3] itoa.c
	[3] itoaw.c
	[3] itob.c
	[4] reverserecursive.c
	[4] swapmacro.c
	[5] pointers/itoawp.c
	[5] pointers/itobp.c
	[5] pointers/reversep.c
	[5] pointers/reverserecursivep.c

void reversesub(char s[], size_t start, size_t end)
void reversesub(char *s, size_t start, size_t end)
	[4] reverserecursive.c
	[5] pointers/reverserecursivep.c

int rightrot(int x, unsigned n);
	[2] rightrot.c

int scompare(char **s, char **t);
	[5] dcl2.c
	[6] wordxref.c
	[-] wordxrefstem.c

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);
	[2] setbits.c

void settabs(int argc, char *argv[], char *tabstop);
	[5] detab2.c
	[5] detab3.c
	[5] entab2.c
	[5] entab3.c

void skipblanks(void);
	[6] define.c

void strcat(char *leftstr, char *rightstr);
	[5] strcat.c

int strindex(char s[], char t[]);
	[4] strrindex.c

int strrindex(char s[], char t[]);
	[4] strrindex.c

size_t strlen(const char *s);
	[3] itoa.c
	[3] itoaw.c
	[3] itob.c
	[5] pointers/itoawp.c
	[5] pointers/itobp.c

void strncat(char *leftstr, char *rightstr, size_t rcount);
	[5] strnfunc/strncat.c

int strncmp(char *s1, char *s2, size_t count) 
	[5] strnfunc/strncmp.c

void strncopy(char *dest, char *source, size_t count);
	[5] strnfunc/strncopy.c

void squeezechar(char s[], char c);
void squeezechar(char *s, char c);
	[2] squeeze.c
	[5] pointers/squeezep.c

void squeeze(char s[], char delete[]);
void squeeze(char *s,  char *delete);
	[2] squeeze.c
	[5] pointers/squeezep.c

size_t squish(size_t pos);
	[1] fold.c

#define swap(t, x, y);
	[4] swapmacro.c

void swap(char *v[], int i, int j);
	[5] readline.c
	[5] readline2.c

void swap(void *v[], int i, int j);
	[5] sort1.c
	[5] sort2.c
	[5] sort3.c
	[5] sort4.c

struct tnode *talloc(void);
	[6] getvars.c
	[6] wordfreq.c
	[6] wordxref.c
	[-] wordxrefstem.c

struct tnode *treeadd(struct tnode *p, char *w, int num, bool *found);
	[6] getvars.c
	[6] wordfreq.c
	[6] wordxref.c

struct tnode *treeadd(struct tnode *p, char *w, char *uw, int line) {
	[-] wordxrefstem.c

void treeprint(struct tnode *p);
	[6] getvars.c
	[6] wordxref.c
	[-] wordxrefstem.c

bool typequal(void);
	[5] dcl2.c

bool typespec(void);
	[5] dcl2.c

void undef(char *s);
	[6] define.c
	[6] tablookup.c

void unescape(char source[], char target[]);
void unescape(char *source,  char *target);
	[3] escape.c
	[3] pointers/escapep.c

void ungetch(char ch);
	[4] rpncalc4-03/lexer.c
	[4] rpncalc4-04/lexer.c
	[4] rpncalc4-05/lexer.c
	[4] rpncalc4-06/lexer.c
	[4] singlegetch.c
	[4] ungets.c
	[4] ungetseof.c
	[5] dcl.c
	[5] dcl2.c
	[5] expr/lexer.c
	[5] getfloat.c
	[5] getint.c
	[5] undcl.c
	[6] define.c
	[6] getvars.c
	[6] getword.c
	[6] wordfreq.c
	[6] wordxref.c
	[-] rpncalc/lexer.c
	[-] getkeywords.c
	[-] wordxrefstem.c

void ungets(char s[]);
	[4] ungets.c
	[4] ungetseof.c
	[5] expr/lexer.c
	[6] define.c

unsigned wordlength(void);
	[2] rightrot.c

void writelines(char *lineptr[], int nlines);
	[5] readline.c
	[5] readline2.c

void writelines(char *lineptr[], int nlines, bool descend);
	[5] sort1.c
	[5] sort2.c
	[5] sort3.c
	[5] sort4.c
