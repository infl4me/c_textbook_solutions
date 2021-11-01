#include <stdio.h>
#include <stdlib.h>

#define NALLOC 1024 /* minimum #units to request */

typedef long Align; /* for alignment to long boundary */

union header
{ /* block header: */
  struct
  {
    union header *ptr; /* next block if on free list */
    unsigned size;     /* size of this block */
  } s;
  Align x; /* force alignment of blocks */
};

typedef union header Header;

static Header base;          /* empty list to get started */
static Header *freep = NULL; /* start of free list */

void *cmalloc(unsigned);
static Header *morecore(unsigned);
void free(void *);

/* cmalloc: general-purpose storage allocator */
void *cmalloc(unsigned nbytes)
{
  Header *p;     /* pointer to current block */
  Header *prevp; /* pointer to previous block */

  unsigned nunits;

  /* round up to allocate in units of sizeof(Header) */
  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

  if ((prevp = freep) == NULL)
  { /* no free list yet */
    base.s.ptr = &base;
    freep = prevp = &base; /* point all to base */
    base.s.size = 0;
  }

  for (p = prevp->s.ptr;; p = p->s.ptr)
  { /* search free linked-list */
    if (p->s.size >= nunits)
    {                          /* big enough */
      if (p->s.size == nunits) /* exactly */
        prevp->s.ptr = p->s.ptr;
      else
      {
        p->s.size -= nunits;
        p += p->s.size; /* allocate at tail-end */
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep)                       /* wrapped around free list */
      if ((p = morecore(nunits)) == NULL) /* request more memory */
        return NULL;                      /* none left */
    prevp = p;                            /* save current pointer's address */
  }
}

/* returns a pointer to n objects of
size size, with the storage initialized to zero */
void *ccalloc(unsigned n, unsigned size)
{
  int i;
  char *p; // init p to char type so that p++ always adds one and we can calc address manualy via size

  p = cmalloc(n * size);

  if (p == NULL)
  {
    return NULL;
  }

  for (i = 0; i < n * size; i++)
  {
    p[i] = 0;
  }

  return p;
}

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
  char *cp; /* pointer to chunk of memory */
  char *sbrk(int);
  Header *up;

  if (nu < NALLOC)
    nu = NALLOC;
  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *)-1) /* no space at all */
    return NULL;
  up = (Header *)cp;
  up->s.size = nu;
  free((void *)(up + 1));
  return freep;
}

/* free: put block ap in free list */
void free(void *ap)
{
  Header *bp, *p;

  bp = (Header *)ap - 1; /* point to block header */
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break; /* free block at start or end of arena */

  if (bp + bp->s.size == p->s.ptr)
  { /* join to upper nbr */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  }
  else
    bp->s.ptr = p->s.ptr;
  if (p + p->s.size == bp)
  { /* join to lower nbr */
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  }
  else
    p->s.ptr = bp;
  freep = p;
}

#define SIZE 20
#define LENGTH 21

int main(void)
{
  int *p, n = 10, i;

  p = ccalloc(n, sizeof(int));

  for (i = 0; i < n; i++)
    printf("%d: (p%ld: %d) \n", i, p + i, p[i]);

  return 0;
}
