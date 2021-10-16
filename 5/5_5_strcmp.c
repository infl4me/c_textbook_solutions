#include <stdio.h>

/* strcmpp: compares at most n characters of t to s */
int strcmpp(char *s, char *t, int n)
{
  while (n--)
  {
    if (*s++ != *t++)
    {
      return 0;
    }
  }

  return 1;
}

int main()
{
  printf("print: %d\n", strcmpp("asdqwe", "asdqwe", 10));
  printf("print: %d\n", strcmpp("asdqwe", "asdqw", 10));
  printf("print: %d\n", strcmpp("asdqwe", "asdqw", 5));

  return 0;
}