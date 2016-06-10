/*
* A basic command-line driven reverse polish-notation calculator
*
* Note: due to 'globbing' in the bash OS X shell (and other *nix I presume), certain operators such as '*'
*       need to be either prefixed with a '\' (e.g. "\*") or enclosed in single quotes (e.g. "'*'") or else
*       it will be interpreted by the shell.
* 
* c.f. http://stackoverflow.com/questions/26288652/surprising-output-of-a-c-program-when-using-to-multiply
*      https://en.wikipedia.org/wiki/Glob_(programming)
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP   100 // Maximum size of operand and operators
#define NUMBER  '0' // Signal for a NUMBER

// External declarations

void   ungets(char s[]);
char   getop(char[]);
void   dapush(double);
double dapop(void);
double dapeek(void);

// Reverse Polish Notation calculator

int main(int argc, char *argv[]) {

	char   operator[MAXOP] = ""; // Operator
	double operand;              // Temporary operand

	// Start the REPL (read, evaluate, and print loop)

	while (--argc > 0) {

		ungets(" ");      // Push end of argument
		ungets(*++argv);  // Push an argument

		switch(getop(operator)) {
			case NUMBER:
				dapush(atof(operator));
				break;
			case '+':
				dapush(dapop() + dapop());
				break;
			case '-':
				operand = dapop();
				dapush(dapop() - operand);
				break;
			case '*':
				dapush(dapop() * dapop());
				break;
			case '/':
				operand = dapop();
				dapush(dapop() / operand);
				break;
			default:
				printf("Error: Unknown command '%s'\n", operator);
				argc = 1;
				break;
		} // switch

	} // while

	printf("%.8g\n", dapop());

	exit(EXIT_SUCCESS);
}