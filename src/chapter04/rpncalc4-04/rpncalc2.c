/*
* A basic reverse polish-notation calculator
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAXOP  100 // Maximum size of operand and operators
#define NUMBER '0' // Signal for a NUMBER

// External declarations

char   getop(char[]);
void   dapush(double);
double dapop(void);
double dapeek(void);
size_t dasize(void);
void   dadup(void);
void   daswap(void);
void   dalist(void);
void   daclear(void);

// Reverse Polish Notation calculator

int main() {

	char   operator[MAXOP] = ""; // Operator
	char   optype;               // Operator type
	double operand;              // Temporary operand
	char   lastop = '\0';        // Last operand

	printf("RPN Calculator (use 'Ctrl-D' to exit)\n\n");
	printf("> ");
	while ((optype = getop(operator)) != (char)EOF) {
		switch(optype) {
			case NUMBER:
				dapush(atof(operator));
				break;
			case '+':
				if (dasize() < 2)
					printf("Less than two items are on the stack\n");
				else
					dapush(dapop() + dapop());
				break;
			case '-':
				if (dasize() < 1)
					printf("Empty stack\n");
				else if (dasize() < 2)
					dapush(-dapop());
				else {
					operand = dapop();
					dapush(dapop() - operand);
				}
				break;
			case '*':
				if (dasize() < 2)
					printf("Less than two items are on the stack\n");
				else
					dapush(dapop() * dapop());
				break;
			case '/':
				if (dasize() < 2)
					printf("Less than two items are on the stack\n");
				else {
					if (fabs(dapeek() - 0) < DBL_EPSILON)
						printf("Error: Attempted to divide by zero.\n");
					else {
						operand = dapop();
						dapush(dapop() / operand);
					}
				}
				break;
			case '%':
				if (dasize() < 2)
					printf("Less than two items are on the stack\n");
				else {
					if (fabs(dapeek() - 0) < DBL_EPSILON)
						printf("Error: Attempted to divide by zero.\n");
					else {
						operand = dapop();
						dapush(fmod(dapop(), operand));
					}
				}
				break;
			case 'P':
				if (dasize() > 0)
					printf("%.8g\n", dapeek());
				break;
			case 'D':
				dadup();
				break;
			case 'S':
				daswap();
				break;
			case 'L':
				dalist();
				break;
			case 'C':
				daclear();
				break;
			case '\n':
				if (lastop != 'P' && lastop != 'L' && dasize() > 0)
					printf("%.8g\n", dapeek());
				printf("> ");
				break;
			default:
				printf("Error: Unknown command '%s'\n", operator);
		} // switch
		lastop = optype;
	} // while

	exit(EXIT_SUCCESS);
}