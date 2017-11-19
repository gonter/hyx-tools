/*
 *  FILE %ds/rdtp/rdtp0103.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-01
 *  latest update: 1997-01-15 10:46:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
struct RDTP_STATE_DEFINITION *rdtp_find_state_definition (
struct RDTP_GENERATOR *gen,
char *state_name)
{
  struct RDTP_STATE_DEFINITION *def= (struct RDTP_STATE_DEFINITION *) 0;
  struct YTREE *yt;

  if (gen != (struct RDTP_GENERATOR *) 0
      && (yt= ytree_insert_word (&gen->state_names,
                                 (unsigned char *) state_name))
            != (struct YTREE *) 0
     )
  {
    if (yt->YT_flags & YTflag_EOW)
    { /* state was already defined */
      def= (struct RDTP_STATE_DEFINITION *) yt->YT_info;
    }
    else
    {
      if ((def= calloc (sizeof (struct RDTP_STATE_DEFINITION), 1))
               != (struct RDTP_STATE_DEFINITION *) 0)
      {
        yt->YT_info= (long) def;
        yt->YT_flags |= YTflag_EOW;
        def->state_name= strdup (state_name);
      }
    }
  }

  return def;
}
