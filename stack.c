#include "antipolish.h"

#define MAXVAL 100 /* maximum depth of val stack */

double ans;

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */



void push(double f)
{	/* push: push f onto value stack */
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		fprintf(stderr,"error: stack full, can't push %g\n", f);
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

void show(void)
{
	printf("\t%.8g\n",(ans=val[sp-1]));
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

void stack_clear(void)
{
	sp=0;
}