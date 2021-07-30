// Ritchie, D. and Kernighan, W. (1988) p86
#ifndef printf
	#include <stdio.h>
#endif
#ifndef isdigit
	#include <ctype.h>
#endif

int getch(void);
void ungetch(int);

int getint(int *pn)
{   /* getint: get next integer from input into *pn */
	signed char c, s=0, sign;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{	s=c;
		c = getch();
	}
	if (!isdigit(c))
	{	if (c!= EOF)
			ungetch(c);
		if (s)
			ungetch(s);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

//original

int getfloat(double *pn)
{   /* getfloat: get next float from input into *pn */
	signed char c, s=0, sign;
	int i=0;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c!= '.') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{	s=c;
		c = getch();
		if (!isdigit(c))
		{	if (c!= EOF)
				ungetch(c);
			if (s)
				ungetch(s);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.')
	{	c = getch();
		if (!isdigit(c))
		{	if (c!= EOF)
				ungetch(c);
			if (s)
				ungetch('.');
			return 0;
		}
		for (;isdigit(c); c = getch(), i++)
			*pn = 10 * *pn + (c - '0');
	}
	for (int j=0;j<i;j++)
		*pn /= 10;
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

// Ritchie, D. and Kernighan, W. (1988) p69

#include <string.h> /* for strlen() */
#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) 
{	/* get a (possibly pushed-back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) 
{	/* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else if (c != EOF)
		buf[bufp++] = c;
}

//original

void unget(char s[])
{
	int l;

	if (bufp + (l=strlen(s)) > BUFSIZE )
		printf("unget: too long string %s\n",s);
	else
		for (int i=0;i<l;++i)
			buf[bufp++] = s[i];
}

// Ritchie, D. and Kernighan, W. (1988) p91

#define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	} else /* not enough room */
		return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
	allocp = p;
}
