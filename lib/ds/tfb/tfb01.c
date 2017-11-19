/*
 *  FILE %ds/tfb/tfb01.c
 *
 *  written:       1994-04-10
 *  latest update: 2001-12-08 21:51:42
 *  $Id: tfb01.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/sbr.h>
#include <gg/tfb.h>
#include <gg/diagnose.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int tfb_get_entry (
const char *keyword,
const char *file_tfb,
const char *file_lut,
char *line_buffer,
int MAX_LINE_BUFFER)
{
  FILE *fi;
  long pos;
  int rc;
  int lng;

  if ((fi= fopen (file_lut, "rb")) == (FILE *) 0)
  {
    gg_diagnose= TFB_ge_no_lut;
    return -1;
  }

  rc= lookup_file (fi, keyword, &pos, &lng);
  fclose (fi);
  if (!(rc & LOOKUP_found)) return 0;

  if ((fi= fopen (file_tfb, "rb")) == (FILE *) 0)
  {
    gg_diagnose= TFB_ge_no_tfb;
    return -1;
  }

  fseek (fi, pos-1L, 0);
  rc= fread_line (fi, line_buffer, MAX_LINE_BUFFER);
  fclose (fi);
  if (rc <= 0)
  {
    gg_diagnose= TFB_ge_tfb_bad;
    return -1;
  }

  return 1;
}
