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

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h> /* for sin, exp, pow, etc. */
#include <stddef.h>  /*for add_remove-string.lb.c */
#include <string.h> /*                           */ 
#include "add_remove-string.lb.c"
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define CMD '1' /* signal that a alphabetic string was found */
#define VAR '2' /* signal for the variable management routine */
int getop(char []);
void getcmd(char s[]);
void getvar(char s[]);
void fifo_print_all(void);
void push(double);
double pop(_Bool idntt);
double fmod(double dend,double sor);
_Bool compare(char s[], char sh[]); /* from add_remove-string.lb.c */
double ans=0;

int main(int argc, char *argv[])
{	/* reverse Polish calculator */
	if (compare(argv[1],"-h"))
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
				getvar(s);
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


#define MAXVAL 100 /* maximum depth of val stack */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

void push(double f)
{	/* push: push f onto value stack */
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(_Bool idntt)
{	/* pop: pop and return top value from stack */
	if (sp > 0)
		return val[--sp];
	else {
		return (double) idntt; /* element of identity: 0.0 for +-, 1.0 for */
	}
}

void fifo_print_all(void)
{
	putchar('\t');
	for (int i=0;i<sp;++i)
		printf("%.8g ",val[i]);
	ans=val[sp-1];
	putchar('\n');
}

inline void show(void)
{
	printf("%.8g ",(ans=val[sp-1]));
}

void duplicate(void)
{
	for (int i=0;i<sp;++i)
		val[sp+i] = val[i];
	sp*= 2;
}

void swap_top(void)
{
	double temp;
	temp = val[sp-1];
	val[sp-1] = val[sp-2];
	val[sp-2] = temp;
}

inline void stack_clear(void)
{
	sp=0;
}


#include <ctype.h> /* for isdigit() */
#include "molon.lb.c"
int getch(void);
void ungetch(int);

int getop(char s[])
{	/* getop: get next character or numeric operand */
	int i;
	char c;
	
	s[0]=' ';
	while ((s[1] = c = getch()) == ' ' || c == '\t' || c == '\n')
		;
	s[2] = '\0';
	if ('a'< c && c < 'z')
		return CMD;
	if ('A' <= c && c <= 'Z')
		return VAR;
	if (!isdigit(c) && c != '.')	
		return c; /* not a number */
	i = 1;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '~')
		s[0] = '-';
	ungetch(c);
	s[i] = '\0';
	return NUMBER;
}

_Bool var_able[26];
float var[26]={0};

void getvar(char s[])
{
	char c,v=s[1];

	while ((c = getch()) == ' ' || c == '\t' || c == '\n')
		;
	if (c == '$')
	{	var[v-'A']=pop(0);
		var_able[v-'A']=1;
	}
	else 
	{	if (var_able[v-'A'])
			push(var[v-'A']);
		else
			printf("error: undefined variable %c\n",v);
		ungetch(c);
	}
}


void show(void);
void stack_clear(void);

void getcmd(char s[])
{
	int i;
	char c;
	double op2;

	for (i=2;(s[i] = c = getch()) != ' ' && c != '\t' && c!= '\n';++i)
		;
	if (compare(s,"showall"))
		fifo_print_all();
	else if (compare(s,"show"))
		show();
	else if (compare(s,"dupp"))
		duplicate();
	else if (compare(s,"swap"))
		swap_top();
	else if (compare (s, "clear"))
		stack_clear();
	else if (compare(s, "sin"))
		push(sin(pop(0)));
	else if (compare(s, "exp"))
		push(exp(pop(1)));
	else if (compare(s, "cos"))
		push(cos(pop(0)));
	else if (compare(s, "pow"))
	{	op2=pop(1);
		push(pow(pop(1),op2));
	}
	else if (compare(s, "log"))
		push(log(pop(1)));
	else if (compare(s, "sqrt"))
		push(sqrt(pop(1)));
	else if (compare(s, "abs"))
		push(fabs(pop(0)));
	else
		printf("error: unknown literal %s\n", s);
	s[i+1]='\0';
	ungetch(c);
}

