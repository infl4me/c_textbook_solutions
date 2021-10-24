#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSTACK 100

/**
* evaluates a reverse Polish expression from the
* command line, where each operator or operand is a separate argument. 
* For example, expr 2 3 4 + *; Evaluates: 2 * (3+4)
 * */
main(int argc, char *argv[])
{
  int op2, d;

  while (--argc > 0)
  {
    switch ((*++argv)[0])
    {
    case '+':
      push(pop() + pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '*':
      push(pop() * pop());
      break;
    case '/':
      op2 = pop();
      push(pop() / op2);
      break;

    default:
      d = atoi(argv[0]);
      if (d)
      {
        push(d);
      }
      else
      {
        printf("Unknown argument: %s\n", argv[0]);
        return -1;
      }

      break;
    }
  }

  if (!is_empty())
    printf("Result: %d", pop());
  else
    printf("Stack is empty");

  return 0;
}

int stack[MAXSTACK];
int sp = 0; /* next free stack position */

/* push: push f onto value stack */
void push(int d)
{
  if (sp < MAXSTACK)
    stack[sp++] = d;
  else
    printf("error: stack full, can't push %d\n", d);
}

/* pop: pop and return top value from stack */
int pop(void)
{
  if (sp > 0)
    return stack[--sp];
  else
  {
    printf("error: stack empty\n");
    return 0;
  }
}

int is_empty(void)
{
  return sp == 0;
}