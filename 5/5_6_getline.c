#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int getlinep(char *, int);
void copy(char to[], char from[]);

/* print the longest input line */
main()
{
  char s[MAXLINE], maxs[MAXLINE];
  int len, max;

  max = 0;

  while ((len = getlinep(s, MAXLINE)) > 0)
  {
    if (len > max)
    {
      max = len;
      copy(maxs, s);
    }
  }

  printf("\nResult: %s", maxs);

  return 0;
}

/* getline: read a line into s, return length */
int getlinep(char *s, int lim)
{
  int c;
  char *sc = s;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
  {
    *s++ = c;
  }

  if (c == '\n')
  {
    *s++ = c;
  }

  *s = '\0';

  return s - sc;
}

void copy(char to[], char from[])
{
  int i;
  i = 0;

  while ((to[i] = from[i]) != '\0')
    ++i;
}