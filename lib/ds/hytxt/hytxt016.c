/*
 *  FILE %ds/hytxt/hytxt016.c
 *
 *  written:       1993-12-26
 *  latest update: 1996-10-13 12:02:58
 *  $Id: hytxt016.c,v 1.2 2002/01/27 23:01:40 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/hytxt.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int hyx_extract (
FILE *fo,
FILE *fi_hyx,
FILE *fi_idx,
FILE *fi_lut,
FILE *fi_xfn,
char *frame_name,
int verbose_mode,
int extract_flags)
{
  long size;                    /* size of the searched frame               */

  if (verbose_mode > 0) printf ("frame \'%s\';", frame_name);

  if ((size= hyx_seek_by_name (fi_hyx, fi_idx, fi_lut, fi_xfn, frame_name))
      < 0L)
    return -1;

  if (verbose_mode > 0) printf (" transfering (%ld)...", size);

  if (extract_flags & HYXEF_add_dot)
  {
    fprintf (fo, "DATA %ld\n", size);
    ftransfer_add_dot (fi_hyx, fo, size);
  }
  else
  {
    ftransfer (fi_hyx, fo, size);
    if (extract_flags & HYXEF_append_eoln) fputc ('\n', fo);
  }

  if (verbose_mode > 0) fputs (" done\n", stdout);

  return 0;
}
