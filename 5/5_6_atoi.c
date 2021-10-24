#include <stdio.h>

int main()
{
  printf("Rsult: %d\n", atoi("123"));
  printf("Rsult: %d\n", atoi("4123"));

  return 0;
}

/* atoi: convert s to integer */
int atoip(char *s)
{
  int n;
  n = 0;

  while (*s >= '0' && *s <= '9')
  {
    n = 10 * n + (*s - '0');
    s++;
  }

  return n;
}
