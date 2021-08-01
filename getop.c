#include <ctype.h> /* for isdigit() */
#include <math.h> /* for sin, exp, pow, etc. */
#include "antipolish.h"
#include "stack.h"

int getch(void);
void ungetch(int);

int getop(char s[])
{	/* getop: get next character or numeric operand */
	int i;
	char c;
	
	s[0]=' ';
	while (isspace(s[1] = c = getch()))
		;
	s[2] = '\0';
	if (islower(c))
		return CMD;
	if (isupper(c))
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

	while (isspace(c = getch()))
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

void getcmd(char s[])
{
	int i;
	char c;
	double op2;

	for (i=2;!isspace(s[i] = c = getch());++i)
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
