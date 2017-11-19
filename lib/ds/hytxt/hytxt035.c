/*
 *  FILE %ds/hytxt/hytxt035.c
 *
 *  seek a frame by index
 *  see also: hyx_seek_by_name ()
 *
 *  written:       1995-12-05
 *  latest update: 1996-10-13 15:40:28
 *
 */

#include <stdio.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
long hyx_seek_by_index (
FILE *fi_hyx,
FILE *fi_idx,
long idx)
{
  long beg;                     /* begin position in cluster                */
  long end;                     /* end position in cluster                  */
  long cln;                     /* cluster number                           */

  if (deref_index (fi_idx, idx, &beg, &end, &cln) == 0
      && beg >= 0L
      && end >= 0L
      && end > beg
     )
  {
    fseek (fi_hyx, beg, 0);
    return end-beg+1L;
  }

  return -1L;
}
