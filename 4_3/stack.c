#include <stdio.h>
#include "calc.h"

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

void print_stack()
{
  int i;

  if (!sp)
  {
    printf("Stack is empty\n");
    return;
  }

  printf("Stack: ");
  for (i = 0; i < sp; i++)
    printf("%.2f ", val[i]);

  printf("\n");
}

void clear_stack()
{
  sp = 0;
  printf("Stack has been cleared\n");
}

/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else
  {
    printf("error: stack empty\n");
    return 0.0;
  }
}