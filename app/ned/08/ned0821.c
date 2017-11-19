/*
 *  FILE %ned/08/ned0821.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  written:       1987 09 08
 *                 1991 01 30: Revision
 *                 1991 06 01: Revision
 *  latest update: 1997-01-26 11:27:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int wr_ftr (FILE *ff, int ln, struct FEATURE *fp, int col, int vcol)
{
  long pos= 0;   /* hier nur dummy! */
  int rv= 0;

  for (; fp != (struct FEATURE *) 0; fp= fp->ftr_next)
  {
    if (fp->ftr_pos == col)
    {
      fprintf (ff, "%3d %3d %3d ", ln, vcol, fp->ftr_type);
      wr_ftr_txt (ff, fp, &pos);
      if (fp->ftr_display_mode == FTR_display_replarray)
        rv += fp->ftr_replarray_size;
      fputc (0x0A, ff);
    }
  }

  return rv;
}
