/*
 *  FILE %sbr/array.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1996-08-11
 *  latest update: 1999-04-25 16:56:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
static struct ARRAY_CONTROL *ac= (struct ARRAY_CONTROL *) 0;

/* ------------------------------------------------------------------------ */
int string_push (char *fn)
{
  if (ac == (struct ARRAY_CONTROL *) 0) ac= array_new ();
  if (ac == (struct ARRAY_CONTROL *) 0) return -1;

  return array_push (ac, (void *) strdup (fn));
}

/* ------------------------------------------------------------------------ */
int string_unshift (char *fn)
{
  if (ac == (struct ARRAY_CONTROL *) 0) ac= array_new ();
  if (ac == (struct ARRAY_CONTROL *) 0) return -1;

  return array_unshift (ac, (void *) strdup (fn));
}

/* ------------------------------------------------------------------------ */
char *string_pop ()
{
  if (ac == (struct ARRAY_CONTROL *) 0) return (char *) 0;

  return (char *) array_pop (ac);
}

/* ------------------------------------------------------------------------ */
char *string_shift ()
{
  if (ac == (struct ARRAY_CONTROL *) 0) return (char *) 0;

  return (char *) array_shift (ac);
}

/* ------------------------------------------------------------------------ */
void string_reset ()
{
  if (ac != (struct ARRAY_CONTROL *) 0)
  {
    array_dispose (ac);
    ac->element_destructor= free;
    ac= (struct ARRAY_CONTROL *) 0;
  }
}
