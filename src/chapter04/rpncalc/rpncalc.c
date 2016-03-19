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

// Reverse Polish Notation calculator

int main() {

	char   operator[MAXOP] = ""; // Operator
	char   optype;               // Operator type
	double operand;              // Temporary operand

	printf("RPN Calculator (use 'Ctrl-D' to exit)\n\n");

	while ((optype = getop(operator)) != (char)EOF) {
		switch(optype) {
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
				if (fabs(operand - 0) < DBL_EPSILON)
					printf("Error: Attempted to divide by zero.");
				else
					dapush(dapop() / operand);
				break;
			case '\n':
				printf("%.8g\n", dapop());
				break;
			default:
				printf("Error: Unknown command '%s'\n", operator);
		} // switch
	} // while

	exit(EXIT_SUCCESS);
}