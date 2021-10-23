#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int strindex(char source[], char searchfor[]);

char pattern[] = "why";

main()
{
  printf("Index: %d", strindex("why would you?", pattern));

  return 0;
}

/* strindex: returns the position of the rightmost occurrence of t in s, or -1 if there is none */
int strindex(char s[], char t[])
{
  int i, j, k;
  for (i = 0; s[i] != '\0'; i++)
  {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
    {
      return i + k - 1;
    }
  }

  return -1;
}