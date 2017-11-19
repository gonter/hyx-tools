/*
 *  FILE %sbr/xref02.c
 *
 *  Cross Reference Generator
 *  - resolver
 *
 *  written:       1997-08-03
 *  latest update: 1997-08-15 21:38:03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/xref.h>

/* ------------------------------------------------------------------------ */
struct XREF_RESOLVE *xref_new_resolve (struct XREF_CONTEXT *ctx)
{
  struct XREF_RESOLVE *res;
  struct ARRAY_CONTROL *ac;

  if (ctx == (struct XREF_CONTEXT *) 0
      || (res= (struct XREF_RESOLVE *)
               calloc (sizeof (struct XREF_RESOLVE), 1))
            == (struct XREF_RESOLVE *) 0
      || (ac= array_new ()) == (struct ARRAY_CONTROL *) 0
     )
    return (struct XREF_RESOLVE *) 0;

  res->ctx= ctx;
  res->unresolved= ac;

  return res;
}

/* ------------------------------------------------------------------------ */
long xref_resolve (
struct XREF_RESOLVE *res,
char *name)                     /* add item to the resolver list */
/* return: -1 .. error; 0 .. already resolved; > 0 number in resolve queue */
{
  struct ARRAY_CONTROL *ac;

  if (res == (struct XREF_RESOLVE *) 0
      || (ac= res->unresolved) == (struct ARRAY_CONTROL *) 0
     ) return (long) -1;

  if (ytree_get_value (res->resolved, (UCHAR *) name) != 0
      || ytree_get_value (res->ignore, (UCHAR *) name) != 0
     )
    return (long) 0;

  array_push (ac, (void *) strdup (name));

  printf ("  resolve %s\n", name);

  return array_elements (ac);
}

/* ------------------------------------------------------------------------ */
/* YTREE_TRACKER: add externals to resolve list */
int xref_resolve_symbols (struct YTREE *yt, char *str, void *cd)
{
  if (yt->YT_flags & YTflag_EOW)
    xref_resolve ((struct XREF_RESOLVE *) cd, str);

  return 0;
}

/* ------------------------------------------------------------------------ */
int xref_ignore (struct XREF_RESOLVE *res, char *name, void *cd)
{
  if (res == (struct XREF_RESOLVE *) 0) return -1;

  ytree_set_value (&res->ignore, (UCHAR *) name, (long) cd);
  return 0;
}

/* ------------------------------------------------------------------------ */
int xref_print_ref_list (long info, char *str, void *cd)
{
  char *msg;

  if ((msg= (char *) cd) == (char *) 0) msg= "";

  printf ("%s %8ld %s\n", msg, info, str);
  return 0;
}
