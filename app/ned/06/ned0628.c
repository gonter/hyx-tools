/*
 *  FILE %ned/06/ned0628.c
 *
 *  take history notes about the file or frame in a window
 *
 *  written:       1993-02-21
 *  latest update: 1995-04-30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int take_history_notes (struct WINDOWCTRL *w)
{
  struct FILECTRL *fc;
  struct FRAMECTRL *frc;
  struct CLUSTERCTRL *cl;

  if ((fc= (struct FILECTRL *) w->file_or_frame) == (struct FILECTRL *) 0)
    return -1;

  if (w->file_type == FTY_HYPER)
  {
    frc= (struct FRAMECTRL *) w->file_or_frame;
    if ((cl= frc->cluster) == (void *) 0) return -1;
    ned_history (cl->cluster_name_hyx, frc->frame_name,
                 cl->cluster_name_logic, w->file_type, w->file_format);
  }
  else
  {
    ned_history (fc->FC_fnm_txt, (char *) 0,
                 w->WC_title_short, w->file_type, w->file_format);
  }

  return 0;
}
