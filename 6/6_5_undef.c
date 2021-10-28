#include <stdio.h>
#include <stdlib.h>

#define IN 1
#define HASHSIZE 101

struct nlist *lookup(char *);
char *strdup(char *);

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct nlist
{                     /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

/* hash: form hash value for string s */
unsigned hash(char *s)
{
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;

  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
  struct nlist *np;
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; /* found */
  return NULL;   /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;
  if ((np = lookup(name)) == NULL)
  { /* not found */
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  else                      /* already there */
    free((void *)np->defn); /*free previous defn */
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

/* undef: remove a name and definition from the hashtab
  returns 1 if removed, else 0;
*/
int undef(char *s)
{
  struct nlist *np = hashtab[hash(s)], *npt;

  if (np == NULL)
  {
    return 0;
  }

  if (strcmp(s, np->name) == 0)
  {
    hashtab[hash(s)] = np->next;
    free((void *)np->defn);
    free((void *)np);
    return 1;
  }

  while (np->next != NULL)
  {
    if (strcmp(s, np->next->name) == 0)
    {
      npt = np->next;
      np->next = np->next->next;
      free((void *)npt->defn);
      free((void *)npt);
      return 1;
    }

    np = np->next;
  }

  return 0;
}

int main()
{
  install("asd", "asd");
  printf("Result: %s\n", lookup("asd")->defn);
  undef("asd");

  if (lookup("asd") == NULL)
  {
    puts("ITS NULL!");
  }
}