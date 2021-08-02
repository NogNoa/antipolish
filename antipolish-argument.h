#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /* for isdigit() */
#include <math.h> /* for sin, exp, pow, etc. */
#include <string.h>

void push(double);
double pop(_Bool idntt);
void fetch_var(char v);
void assign_var(char v);
void shortop(char op);
void getcmd(char s[]);

double ans;
