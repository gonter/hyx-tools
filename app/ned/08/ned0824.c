/*
 *  FILE %ned/08/ned0824.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  written:       1991 02 07
 *  latest update: 1997-01-26 11:21:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int wr_sgml_tag (FILE *ff, struct FEATURE *fp, int col_idx, long *position)
{
  int rv=0;

  for (; fp != (struct FEATURE *) 0; fp= fp->ftr_next)
  {
    if (fp->ftr_pos == col_idx)
    {
      wr_ftr_txt (ff, fp, position);
      if (fp->ftr_display_mode == FTR_display_replarray)
        rv += fp->ftr_replarray_size;
    }
  }
  return rv;

  /* versteckte Features koennten mehrere auf einer                     */
  /* Column sitzen. Features mit Pseudo Character koennen immer         */
  /* nur einzeln an einer Column Position sitzen.                       */
  /* Es kann der Fall eintreten, dass mehrere versteckte Features       */
  /* an einer Column Position zusammen mit hoechstens einem Feature     */
  /* mit Pseudo Character sitzt. In diesem Fall muss eben dieser        */
  /* eine Pseudo Character entfernt werden.                             */
}
