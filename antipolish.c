// Ritchie, D. and Kernighan, W. (1988) p69
//freely edited

/*
	Allowed input:
				  digits for numbers,
				  lowercase for commands some operators,
				  UPPER CASE for variables,
				  symbols for the rest of the operators.
	

	unary operators : ~, :, $, sin, cos, exp, log, sqrt, abs
	binary operators: +, -, *, /, %, pow
	control commands: =, show, showall, dupp, swap, clear
	
	
	the calculator use polish notation, every operator is postfixial	

	Variables are single uppercase letter, they are assigned with 
	$ and called without it
	
	Example: "3 A &" assigns 3 to A. "2 A * =" than returns "6". 
	
	_ is variable that is always assigned the last printed value.


	=    returns the most recent input or product and remove it from the stack
	show	does the same without removing it.
	showall		prints the whole stuck
	dupp	duplicate the whole stuck (AB -> ABAB, not AABB)
	swap	swaps the last two elements on top of the stack
	clear 	deletes the stack.
	~	is the unary - (turns positive to negative and v.v)
	:	turns a number into its reciprocal.  
	% 	is mod division

*/

/* gcc with add_remove-string.lb.c */

#include <stdlib.h> /* for atof() */
#include "antipolish.h"

#define MAXOP 100 /* max size of operand or operator */

int getop(char []);
void getcmd(char s[]);
void getvar(char s);
double fmod(double dend,double sor);
double floor(double);
double ans=0;

int main(int argc, char *argv[])
{	/* reverse Polish calculator */
	if (argc > 1 && compare(argv[1],"-h"))
	{	printf("\tAllowed input:\r\n\t\t\t\t  digits for numbers,\r\n\t\t\t\t  lowercase for commands some operators,\r\n\t\t\t\t  UPPER CASE for variables,\r\n\t\t\t\t  symbols for the rest of the operators.\r\n\t\r\n\r\n\tunary operators : ~, :, $, sin, cos, exp, log, sqrt, abs\r\n\tbinary operators: +, -, *, /, %%, pow\r\n\tcontrol commands: =, show, showall, dupp, swap, clear\r\n\t\r\n\t\r\n\tthe calculator use polish notation, every operator is postfixial\t\r\n\r\n\tVariables are single uppercase letter, they are assigned with \r\n\t$ and called without it\r\n\t\r\n\tExample: \"3 A &\" assigns 3 to A. \"2 A * =\" than returns \"6\". \r\n\t\r\n\t_ is variable that is always assigned the last printed value.\r\n\r\n\r\n\t=    returns the most recent input or product and remove it from the stack\r\n\tshow\tdoes the same without removing it.\r\n\tshowall\t\tprints the whole stuck\r\n\tdupp\tduplicate the whole stuck (AB -> ABAB, not AABB)\r\n\tswap\tswaps the last two elements on top of the stack\r\n\tclear \tdeletes the stack.\r\n\t~\tis the unary - (turns positive to negative and v.v)\r\n\t:\tturns a number into its reciprocal.  \r\n\t%% \tis mod division\r\n\n");
		return 0;
	}
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
			break;
			case '_':
				push(ans);
			break;
			case CMD:
				getcmd(s);
			break;
			case VAR:
				getvar(s[1]);
			break;
			case '+':
				push(pop(0) + pop(0));
			break;
			case '*':
				push(pop(1) * pop(1));
			break;
			case '-':
				op2 = pop(0);
				push(pop(0) - op2);
			break;
			case '/':
				op2 = pop(1);
				if (op2 != 0.0)
					push(pop(1) / op2);
				else
					printf("error: zero divisor\n");
			break;
			case '%':
				op2 = pop(1);
				if (op2 != 0)
					push(fmod(pop(0),op2));
				else
					printf("error: zero divisor\n");
			break;
			case ':':
				push(1/pop(1));
			break;
			case '=':
				printf("\t%.8g\n", (ans=pop(0)));
			break;
			default:
				printf("error: unknown command %s\n", s);
			break;
		}
	}
	fifo_print_all();
	return 0;
}

inline double fmod(double dend,double sor)
{
	return dend - floor( dend / sor) * sor;
}
