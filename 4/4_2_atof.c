#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 1000 /* maximum input line length */

double atof(char string[]);

main()
{
  printf("Result: %f", atof("1.701e+2"));

  return 0;
}

/* atof:  convert string s to double */
double atof(char s[])
{
  double val, power, epower;
  int i, sign, esign;
  for (i = 0; isspace(s[i]); i++) /* skip white space */
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++)
  {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }

  if (s[i] == 'e' || s[i] == 'E')
    i++;

  if (s[i] == '-' || s[i] == '+')
  {
    esign = s[i] == '-' ? -1 : 1;
    i++;
  }

  for (epower = 0; isdigit(s[i]); i++)
    epower = 10 * epower + (s[i] - '0');

  return sign * val / power * pow(10, epower * esign);
}