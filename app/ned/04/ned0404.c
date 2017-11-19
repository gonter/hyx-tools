/*
 *  FILE %ned/04/ned0404.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1993 01 18: remote file read and write via dorothy
 *                 1993-01-31: removed dorothy and installed IOA
 *                             (indirect object access) instead
 *  latest update: 1997-08-03 15:46:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/filename.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_w_save (struct WINDOWCTRL *w, int flg)
/* RETURN: < 0 ... error                        */
/*         = 0 ... ok                           */
{
  struct LINE *la;
  struct FILECTRL *fc;
  struct FRAMECTRL *frc;
  struct CLUSTERCTRL *cc;
  long la_offset, lz_offset;
  int rc= 0;
  char *outfile;
  char *ftrfile;
  int outmode;

  if (w->WC_edit_mode & EDIT_READ_ONLY)
     return 0;                          /* OK: read only mode -> no save    */

  for (la= w->first;
       la != (struct LINE *) 0 && la->prev != (struct LINE *) 0;
       la= la->prev);

  if (w->file_type == FTY_HYPER)
  { /* HyperText Frame */

    if ((frc= (struct FRAMECTRL *) w->file_or_frame) == (void *) 0
        || (cc= frc->cluster) == (struct CLUSTERCTRL *) 0
       ) return -1;

    outfile= cc->cluster_name_hyx;
    outmode= FLG2_append_mode;    /* append to file! */

    rc= ned_f_write (w,
                 outfile,
                 (char *) 0,
                 0,
                 1,
                 la,
                 (struct LINE *) 0,
                 &frc->frame_begin,
                 &frc->frame_end,
                 outmode);              /* append !!! */

    update_index (cc, frc->frame_index,
                  frc->frame_begin, frc->frame_end, 0L);

    if (frc->frame_lookup == FRAME_is_new)
    {
      FILE *xfn;

      frc->frame_lookup= FRAME_in_XFN;
      if ((xfn= fopen (cc->cluster_name_xfn, "ab")) != (FILE *) 0)
      {
        fprintf (xfn, "%lx %s\n", frc->frame_index, frc->frame_name);
        fclose (xfn);
      }
    }

    frc->upd= 0;
  }
  else
  { /* normales File */

    if ((fc= (struct FILECTRL *) w->file_or_frame) == (struct FILECTRL *) 0)
      return -1;

    outfile= fc->FC_fnm_txt;
    ftrfile= fc->FC_fnm_ftr;

    rc= ned_f_write (w,
                 outfile,
                 ftrfile,
                 flg,
                 1,
                 la,
                 (struct LINE *) 0 /* Dummy */,
                 &la_offset,
                 &lz_offset,
                 FLG2_none);

    fc->FC_upd= 0;
  }

  if (rc == 0) w->f_upd= 0;

  return rc;
}
