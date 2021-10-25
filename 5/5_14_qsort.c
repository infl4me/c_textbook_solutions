#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

static char *months[] = {
    "Illegal month",
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"};

char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void mqsort(void *lineptr[], int left, int right,
            int (*comp)(void *, void *), int reverse);
int numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[])
{
  int nlines;      /* number of input lines read */
  int numeric = 0; /* 1 if numeric sort */
  int reverse = 0;

  if (argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;

  if (argc > 2 && strcmp(argv[2], "-r") == 0) // naive implementation
    reverse = 1;
  writelines(argv, argc);
  mqsort((void **)months, 0, 12,
         (int (*)(void *, void *))(numeric ? numcmp : strcmp), reverse);
  writelines(months, 13);
}

/* mqsort:  sort v[left]...v[right] into increasing order */
void mqsort(void *v[], int left, int right,
            int (*comp)(void *, void *), int reverse)
{
  int i, last;
  void swap(void *v[], int, int);
  if (left >= right) /* do  nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
  {
    if (reverse ? ((*comp)(v[i], v[left]) > 0) : ((*comp)(v[i], v[left]) < 0))
      swap(v, ++last, i);
  }

  swap(v, left, last);
  mqsort(v, left, last - 1, comp, reverse);
  mqsort(v, last + 1, right, comp, reverse);
}

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void swap(void *v[], int i, int j)
{
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}