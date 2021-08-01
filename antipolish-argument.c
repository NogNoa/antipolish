#include "antipolish-argument.h"

void getop2(char*);

int main(int argc, char *argv[])
{
	for (;argc>0;argc--)
		getop2(*argv++);
	return 0;
}

void getop2(char* arg)
{
	_Bool num=1;
	char c;
	double op2;

	for (int i=0;(c=arg[i++]) && (num &= isdigit(c));)
		;
	if (num)
		push(atof(arg));
	else if (strlen(arg) == 1)
		switch (*arg) {
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
					fprintf(stderr,"error: zero divisor\n");
			break;
			case '%':
				op2 = pop(1);
				if (op2 != 0)
					push(fmod(pop(0),op2));
				else
					fprintf(stderr,"error: zero divisor\n");
			break;
			case ':':
				push(1/pop(1));
			break;
			case '=':
				printf("\t%.8g\n", (ans=pop(0)));
			break;
			default:
				fprintf(stderr,"error: unknown command %s\n", arg);
			break;
		}
	else
		fprintf(stderr,"error: unknown command %s\n", arg);
}