#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

// Memory allocator by Kernighan and Ritchie,
// The C programming Language, 2nd ed.  Section 8.7.

typedef long Align;

union header {
  struct {
    union header *ptr;
    uint size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep;

void
free(void *ap)
{
  Header *bp, *p;

  bp = (Header*)ap - 1;
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  if(bp + bp->s.size == p->s.ptr){
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  if(p + p->s.size == bp){
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}

static Header*
morecore(uint nu)
{
  char *p;
  Header *hp;

  if(nu < 4096)
    nu = 4096;
  p = sbrk(nu * sizeof(Header));
  // p = brk((int)(*p) + nu * sizeof(Header));
  if(p == (char*)-1)
    return 0;
  hp = (Header*)p;
  hp->s.size = nu;
  free((void*)(hp + 1));
  return freep;
}

void*
malloc(uint nbytes)
{
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
  if((prevp = freep) == 0){
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
    if(p->s.size >= nunits){
      if(p->s.size == nunits)
        prevp->s.ptr = p->s.ptr;
      else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void*)(p + 1);
    }
    if(p == freep)
      if((p = morecore(nunits)) == 0)
        return 0;
  }
}

void*
calloc(int n, uint type)
{
  void* p;
  if ((p = malloc(n * type)) == 0)
    return 0;

  memset(p, 0, type);
  return p;
}

void* 
valloc(int n, uint size, void* value)
{
    char* cp_val = (char*)value;
    void *p;
    if ((p = malloc(n * size)) == 0)
        return 0;
    for (int i = 0; i < n; i++) {
        char* pp = ((char*)p) + (i * size);
        for(int j = 0;j < size; j++) {
            pp[j] = cp_val[j];
        }
    }
    return p;
}

void*
realloc(void* src, int n, int m, uint type) {
  void* p;
  if ((p = malloc(m * type)) == 0)
    return 0;
  
  char* cp_src = (char*)src;
  for (int i = 0; i < n; i++) {
    char* pp = ((char*)p) + (i * type);
    for (int j = 0; j < type; j++) {
      pp[j] = cp_src[i * type + j];
    }
  }
  return p;
}