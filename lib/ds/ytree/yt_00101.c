/*
 *  FILE %ds/ytree/yt_00101.c
 *
 *  ytree_alloc: create a new YTREE node
 *
 *  written:       1996-12-11
 *  latest update: 1996-12-11 12:47:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/signatur.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
struct YTREE_CONTROL *ytree_new_control (char *name)
{
  struct YTREE_CONTROL *nc;

  if ((nc= (struct YTREE_CONTROL *)
           calloc (sizeof (struct YTREE_CONTROL), 1))
        != (struct YTREE_CONTROL *) 0
     )
  {
    nc->signature= SIG_YTREE_CONTROL;
    if (name != (char *) 0) nc->name= strdup (name);
  }

  return nc;
}
