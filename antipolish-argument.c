#include "antipolish-argument.h"

void parse(char*);

double ans=0;

int main(int argc, char *argv[])
{
	for (argv++;argc>1;argc--)
		parse(*argv++);
	return 0;
}

void parse(char* arg)
{
	_Bool num=1, low=1;
	char c;


	for (int i=0;(c=arg[i++]) && num ;)
		if (!isdigit(c))
			num = 0;
	for (int i=0;(c=arg[i++]) && low ;)
		if (!islower(c))
			low = 0; 
	if (num)
		push(atof(arg));
	else if (isupper(arg[0]) && arg[1] == '$')
		assign_var(arg[0]);
	else if (strlen(arg) == 1)
		shortop(*arg);
	else if (low)
	{
		getcmd(arg);
	}
	else
		fprintf(stderr,"error: unknown command %s\n", arg);
}