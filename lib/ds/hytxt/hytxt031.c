/*
 *  FILE %ds/hytxt/hytxt031.c
 *
 *  written:       1995-05-21
 *  latest update: 1996-03-24 17:47:31
 *  $Id: hytxt031.c,v 1.2 2002/01/27 23:01:41 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/sbr.h>
#include <gg/sgml.h>
#include <gg/parse.h>
#include <gg/hytxt.h>

static long end_tags [] = { SGML_TAG_endframe };

/* ------------------------------------------------------------------------ */
int hyx_thr_extract (
FILE *fo,
FILE *fi_hyx,
FILE *fi_idx,
FILE *fi_lut,
FILE *fi_xfn,
char *frame_name,
int verbose_mode,
int extract_flags,
char *wanted_thread)
{
  struct TEXT_ELEMENT *te= (struct TEXT_ELEMENT *) 0;
  struct HYX_PARSER_CLASS *hpc;
  long chars_read;
  long size;
  int rc;

  if (verbose_mode > 0) printf ("frame \'%s\';", frame_name);

  if ((size= hyx_seek_by_name (fi_hyx, fi_idx, fi_lut, fi_xfn, frame_name))
             < 0L
      || (hpc= hyx_init_parser_class ()) == (struct HYX_PARSER_CLASS *) 0
     )
    return -1;

  if (verbose_mode > 0) printf (" transfering (%ld)...", size);

  if (extract_flags & HYXEF_write_frame_name)
  {
    fputs (frame_name, stdout);
    fputc ('\n', stdout);
  }

  rc= hyx_parse1_file (hpc, fi_hyx, &te, end_tags, 1, size, &chars_read);

  if (rc == 0 && chars_read > 0L)
  {
    hyx_thr_process (fo, fi_hyx, fi_idx, fi_lut, fi_xfn,
                     verbose_mode, extract_flags, wanted_thread,
                     te, 0, 0);

    /* ftransfer (fi_hyx, fo, size); */

    if (extract_flags & HYXEF_append_eoln) fputc ('\n', fo);
  }

  if (verbose_mode > 0) fputs (" done\n", stdout);
  hyx_frtx_elem_list (te);

  return 0;
}
