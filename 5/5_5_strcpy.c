#include <stdio.h>

/* strncpy: copies at most n characters of t to s */
void strncpyp(char *s, char *t, int n)
{
  while (n-- > 0 && (*s++ = *t++))
    ;
}

int main()
{
  char s[100];

  strncpyp(s, "asdqwe", 5);

  printf("print: %s\n", s);

  return 0;
}