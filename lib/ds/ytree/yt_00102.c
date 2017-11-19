/*
 *  FILE %ds/ytree/yt_00102.c
 *
 *  ytree_free_control:
 *    destroy a complete ytree control structure
 *    together with the represented ytree
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
#include <gg/strings.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_free_control (struct YTREE_CONTROL *yc)
{
  YTREE_INFO_PROCESSOR *yt_dt;
  void *yt_dt_cd;

  if (yc == (struct YTREE_CONTROL *) 0) return 0;

  if ((yt_dt= yc->destructor) != (YTREE_INFO_PROCESSOR *) 0)
  {
    yt_dt_cd= yc->destructor_cd;
    ytree_process_info (yc->yt, yt_dt, yt_dt_cd);
  }

  ytree_free (yc->yt);
  free_or_what (yc->name);
  free (yc);

  return 0;
}
