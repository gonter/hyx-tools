/*
 *  FILE %ds/lxs/lxs_2001.c
 *
 *  lexicon services
 *
 *  written:       1996-12-20
 *  latest update: 1996-12-22 11:47:57
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/lxs2.h>

/* ------------------------------------------------------------------------ */
struct LEXICON_CONTEXT *lxs_new_context (char *name)
{
  struct LEXICON_CONTEXT *lxc;

  if ((lxc= (struct LEXICON_CONTEXT *)
           calloc (sizeof (struct LEXICON_CONTEXT), 1))
       != (struct LEXICON_CONTEXT *) 0)
  {
    lxc->to_lower= 1;           /* T2D */

    lxc->name= strdup (name);
  }

  return lxc;
}
