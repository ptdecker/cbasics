/*
* tablookup(): Hash table look-up routines
*/

/*@ -unqualifiedtrans -nullderef -mustfreefresh -onlytrans -kepttrans */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constant definitions

#define HASHSIZE 101

// Structures

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

// Globals

static struct nlist *hashtab[HASHSIZE]; // Pointer table

/*
 * strdup(): make a duplicate copy of s
 */

static char *mystrdup(char *s) {

	char *p = (char *)malloc(strlen(s) + 1);

	if (p == NULL) {
		printf("Error: ran out of memory");
		exit(EXIT_FAILURE);
	}

	strcpy(p, s);
	return p;
}

/*
 * hash(): Calculates a hash value for a given string
 */

static unsigned hash(char *s) {

	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

/*
 * lookup(): Look for s in the hash table
 */

static struct nlist *lookup(char *s) {

	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;  // Found

	return NULL; // Not found
}

/*
 * install(): Put a value into the hash table
 */

static struct nlist *install(char *name, char *defn) {

	struct nlist *np;

	if ((np = lookup(name)) == NULL) {

		// Value not found in hash table so add it

		unsigned hashval;

		if ((np = (struct nlist *)malloc(sizeof(*np))) == NULL) {
			printf("Error: ran out of memory");
			exit(EXIT_FAILURE);
		}
		hashval  = hash(name);
		np->name = mystrdup(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;

	} else

		// Value found so free up the previous value (to be replaced with the new)

		free((void *)np->defn);

	np->defn = mystrdup(defn);

	return np;
}

/*
 * undef(): remove a name and definition from the table
 */

static void undef(char *s) {

	unsigned h;
	struct nlist *prior;
	struct nlist *np;

	prior = NULL;
	h = hash(s);

	for (np = hashtab[h]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0)
			break;
		prior = np;
	}

	if (np != NULL) {
		if (prior == NULL)
			hashtab[h] = np->next;
		else
			prior->next = np->next;

		free((void *)np->name);
		free((void *)np->defn);
		free((void *)np);
	}

}

/*
 * Main
 */

int main(void) {

	struct nlist *np;

	printf("The hash value for 'P. Todd Decker' is: %u\n", hash("P. Todd Decker"));


	printf("Installing some key-value pairs...\n");
	(void)install("name",    "P. Todd Decker");
	(void)install("street",  "15203 Maple Street");
	(void)install("city",    "Overland Park");
	(void)install("state",   "Kansas");
	(void)install("zipcode", "66223");

	np = lookup("name");
	printf("Looking up 'name'   : %s\n", (np == NULL) ? "Not found" : np->defn);
	np = lookup("street");
	printf("Looking up 'street' : %s\n", (np == NULL) ? "Not found" : np->defn);
	np = lookup("city");
	printf("Looking up 'city'   : %s\n", (np == NULL) ? "Not found" : np->defn);
	np = lookup("state");
	printf("Looking up 'state'  : %s\n", (np == NULL) ? "Not found" : np->defn);
	np = lookup("zipcode");
	printf("Looking up 'zipcode': %s\n", (np == NULL) ? "Not found" : np->defn);
	np = lookup("phone");
	printf("Looking up 'phone'  : %s\n", (np == NULL) ? "Not found" : np->defn);

	printf("Changing 'zipcode'...\n");
	(void)install("zipcode", "64063");

	np = lookup("zipcode");
	printf("Looking up 'zipcode': %s\n", (np == NULL) ? "Not found" : np->defn);

	printf("Uninstalling 'name'\n");
	undef("name");
	np = lookup("name");
	printf("Looking up 'name': %s\n", (np == NULL) ? "Not found" : np->defn);


	exit(EXIT_SUCCESS);
}