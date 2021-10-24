#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

#define MAXOP 100 /* max size of operand or operator */

// commands
#define CLEAR "clear"
#define PRINT "print"

/* reverse Polish calculator */
int main()
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
  {
    switch (type)
    {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      push((int)pop() % (int)op2);
      break;
    case COMMAND:
      if (!strcmp(s, PRINT))
      {
        print_stack();
      }
      else if (!strcmp(s, CLEAR))
      {
        clear_stack();
      }
      else
      {
        printf("error: unknown special command '%s'\n", s);
      }
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}