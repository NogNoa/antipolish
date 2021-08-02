#include "antipolish-argument.h"
#include "stack.h"

void shortop(char op)
{
	double opand2;
	
	if (isupper(op))
		fetch_var(op);
	else switch (op) {
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
			opand2 = pop(0);
			push(pop(0) - opand2);
		break;
		case '/':
			opand2 = pop(1);
			if (opand2 != 0.0)
				push(pop(1) / opand2);
			else
				fprintf(stderr,"error: zero divisor\n");
		break;
		case '%':
			opand2 = pop(1);
			if (opand2 != 0)
				push(fmod(pop(0),opand2));
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
			fprintf(stderr,"error: unknown operator %c\n", op);
		break;
		}
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

void getcmd(char s[])
{
	if (!strcmp(s,"showall"))
		fifo_print_all();
	else if (!strcmp(s,"show"))
		show();
	else if (!strcmp(s,"dupp"))
		duplicate();
	else if (!strcmp(s,"swap"))
		swap_top();
	else if (!strcmp (s, "clear"))
		stack_clear();
	else if (!strcmp(s, "sin"))
		push(sin(pop(0)));
	else if (!strcmp(s, "exp"))
		push(exp(pop(1)));
	else if (!strcmp(s, "cos"))
		push(cos(pop(0)));
	else if (!strcmp(s, "pow"))
	{	double op2=pop(1);
		push(pow(pop(1),op2));
	}
	else if (!strcmp(s, "log"))
		push(log(pop(1)));
	else if (!strcmp(s, "sqrt"))
		push(sqrt(pop(1)));
	else if (!strcmp(s, "abs"))
		push(fabs(pop(0)));
	else
		printf("error: unknown literal %s\n", s);
}

