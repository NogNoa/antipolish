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
	_Bool num=1;
	char c;
	double op2;

	for (int i=0;(c=arg[i++]) && num ;)
		if (!isdigit(c))
			num =0;
	if (num)
		push(atof(arg));
	else if (isupper(arg[0]) && arg[1] == '$')
		assign_var(arg[0]);
	else if (strlen(arg) == 1)
		if (isupper(*arg))
			fetch_var(*arg);
		else switch (*arg) {
			case '_':
					push(ans);
			break;
			case '+':
				push(pop(0) + pop(0));
			break;
			case '*':
			case 'x':
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
			case '~':
				push(-pop(0));
			break;
			case '=':
			case '\n':
				printf("\t%.8g\n", (ans=pop(0)));
			break;
			default:
				fprintf(stderr,"error: unknown command %s\n", arg);
			break;
		}
	else
		fprintf(stderr,"error: unknown command %s\n", arg);
}