/*
 *  FILE %ds/rdtp/rdtp0105.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-02
 *  latest update: 1996-04-02 18:50:27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_print_states (struct YTREE *yt, void *cd)
{
  FILE *fo;
  struct RDTP_STATE_DEFINITION *st;
  struct RDTP_STATE_TRANSITION *tr;

  if (yt == (struct YTREE *) 0
      || !(yt->YT_flags & YTflag_EOW)
      || (st= (struct RDTP_STATE_DEFINITION *) yt->YT_info)
           == (struct RDTP_STATE_DEFINITION *) 0
     )
    return 0;

  fo= (FILE *) cd;
  fprintf (fo, "state: %s\n", st->state_name);

  for (tr= st->trans; tr != (struct RDTP_STATE_TRANSITION *) 0; tr= tr->next)
    rdtp_print_state_entry (fo, tr, "  ");

  return 0;
}
