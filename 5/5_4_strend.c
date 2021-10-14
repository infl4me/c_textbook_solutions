#include <stdio.h>
#include <string.h>

/* strend: returns 1 if the string t occurs at the
end of the string s, and zero otherwise */
int strendp(char *s, char *t)
{
  char *se, *te;
  se = s + strlen(s);
  te = t + strlen(t);

  while (te > t && *--se == *--te)
  {
  }

  return te == t ? 1 : 0;
}

int main()
{
  printf("print: %d\n", strendp("asd", "d"));
  printf("print: %d\n", strendp("asd", "sd"));
  printf("print: %d\n", strendp("asd", "asd"));
  printf("print: %d\n", strendp("asd", "as"));

  return 0;
}