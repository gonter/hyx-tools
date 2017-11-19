/*
 *  FILE ~/usr/aisbr/unify/unify005.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-12
 *
 */

#include <malloc.h>
#include <gg/unify.h>

long FEATURE_STRUCTURE_allocated=0L;

/* ------------------------------------------------------------------------ */
struct FEATURE_STRUCTURE *fs_allocate_FEATURE_STRUCTURE ()
{
  struct FEATURE_STRUCTURE *x;

  if ((x= calloc (sizeof (struct FEATURE_STRUCTURE), 1))
      != (void *) 0) FEATURE_STRUCTURE_allocated++;

  return x;
}
