#include <stdio.h>

/* strcat: concatenates at most n characters t to end of s; s must be big enough (pointer version) */
void strcatp(char *s, char *t, int n)
{
  // Find the end of s
  while (*++s)
    ;

  // copy t to the end of s
  while (n-- && (*s++ = *t++))
    ;
}

int main()
{
  char s[] = "asd", t[] = "qwerty";

  strcatp(s, t, 3);

  printf("print: %s\n", s);

  return 0;
}