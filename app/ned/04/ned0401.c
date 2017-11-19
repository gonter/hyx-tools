/*
 *  FILE %ned/04/ned0401.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1993-01-18: remote file/frame read via dorothy
 *                 1993-01-31: removed dorothy and installed IOA
 *                             (indirect object access) instead
 *  latest update: 1997-08-03 15:44:27
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <gg/filename.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void s_fget (struct WINDOWCTRL *w)
{
  struct LINE *la= (struct LINE *) 0;
  struct LINE *lb= (struct LINE *) 0;
  struct FILECTRL *fc;
  struct FRAMECTRL *frc;
  struct CLUSTERCTRL *cc;
  int rc= -1;

  w->cx= w->ax;
  w->cy= w->ay;
  w->hv= 0;
  w->znr= 1;
  w->ins_flg= INSFLG_insert;

  if (w->file_type == FTY_HYPER)
  {
    frc= (struct FRAMECTRL *) w->file_or_frame;

    if (frc != (struct FRAMECTRL *) 0 && frc->frame_lookup != FRAME_is_new)
    {
      cc= frc->cluster;
      if (cc != (struct CLUSTERCTRL *) 0)
      {
        if (frc->links > 1)
             frc->links--;                 /* ????????? */
        else ned_lines_free (w->WC_first);

        rc= ned_f_read (w,
                    cc->cluster_name_hyx,
                    (char *) 0,
                    0,
                    &la,
                    &lb,
                    frc->frame_begin,
                    frc->frame_end);
      }
    }
  }
  else
  {
    fc= (struct FILECTRL *) w->file_or_frame;
    if (fc != (struct FILECTRL *) 0)
    {
      if (fc->FC_links > 1)
           fc->FC_links--;                 /* ????????? */
      else ned_lines_free (w->WC_first);

      rc= ned_f_read (w,
                  fc->FC_fnm_txt,
                  fc->FC_fnm_ftr,
                  1,
                  &la,
                  &lb,
                  0L,
                  0x7FFFFFFFL);
    }
  }

  w->WC_act= w->first= la;
  if (w->znr < 1) w->znr= 1;
  w->w_upd |= 0x02;

  if (rc == 1 && la != (struct LINE *) 0)
  {
    rc= w->cx;
    w->cx += w->ax - w->hv;
    if (w->cx > w->bx || w->cx < w->ax)
    { /* hv und cx neu einrichten */
      w->cx= (w->bx - w->ax)/2;
      w->hv= rc - w->cx;
      w->cx += w->ax;
    }

    ned_jmp_2line_by_nr (w, w->znr, 0);
    /* Note: line number is read from feature file, WC_act can point        */
    /*       to somewhere else                                              */
  }
}
