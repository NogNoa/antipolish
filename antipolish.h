#include <stdio.h>

#define NUMBER '0' /* signal that a number was found */
#define CMD '1' /* signal that a alphabetic string was found */
#define VAR '2' /* signal for the variable management routine */

_Bool compare(char s[], char sh[]);
void push(double);
double pop(_Bool idntt);
void fifo_print_all(void);

double ans;
