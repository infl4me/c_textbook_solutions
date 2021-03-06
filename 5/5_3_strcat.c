#include <stdio.h>

/* strcat: concatenate t to end of s; s must be big enough (pointer version) */
void strcatp(char *s, char *t)
{
  // Find the end of s
  while (*++s)
    ;

  // copy t to the end of s
  while (*s++ = *t++)
    ;
}

int main()
{
  char s[100] = "asd", t[] = "qwe";

  strcatp(s, t);

  printf("Result: %s\n", s);

  return 0;
}