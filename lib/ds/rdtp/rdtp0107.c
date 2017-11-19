/*
 *  FILE %ds/rdtp/rdtp0107.c
 *
 *  *** NOT USED, OBSOLTE ***
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-02
 *  latest update: 1996-09-14 22:47:29
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_drop_tables (struct YTREE *yt, void *cd)
{
  if (yt == (struct YTREE *) 0 || !(yt->YT_flags & YTflag_EOW)) return 0;

  return rdtp_drop_state_table (
           (struct RDTP_GENERATOR *) cd,
           (struct RDTP_STATE_DEFINITION *) yt->YT_info);
}
