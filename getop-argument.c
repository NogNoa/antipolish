#include <stdio.h>

void push(double);
double pop(_Bool idntt);

void shorthop(char op)
{
	;
}

_Bool var_able[26];
float var[26]={0};

void fetch_var(char v)
{
	if (var_able[v-'A'])
		push(var[v-'A']);
	else
		fprintf(stderr,"error: unassigned variable %c\n",v);
}


void assign_var(char v)
{
	var[v-'A']=pop(0);
	var_able[v-'A']=1;
}
