/*
 *  FILE %ds/rdtp/rdtp0108.c
 *
 *  mark all state tables as unusued
 *
 *  written:       1996-04-02
 *  latest update: 1996-06-22 12:47:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_unmark_states (struct YTREE *yt, void *cd)
{
  struct RDTP_STATE_DEFINITION *st;

#ifdef MSDOS
  cd;
#endif

  if (yt == (struct YTREE *) 0
      || !(yt->YT_flags & YTflag_EOW)
      || (st= (struct RDTP_STATE_DEFINITION *) yt->YT_info)
           == (struct RDTP_STATE_DEFINITION *) 0
     )
    return 0;

#ifdef DEBUG
  printf ("mark state: %s unused\n", st->state_name);
#endif /* DEBUG */

  st->state_used= 0;
  rdtp_drop_state_table ((struct RDTP_GENERATOR *) cd, st);

  return 0;
}
