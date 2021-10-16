#include <stdio.h>

/* strncpy: copies at most n characters of t to s */
void strncpyp(char *s, char *t, int n)
{
  while (n > 0 && (*t++ = *s++))
  {
    n--;
  }
}

int main()
{
  char *t;

  strncpyp("asdqwe", t, 5);

  printf("print: %s\n", t);

  return 0;
}