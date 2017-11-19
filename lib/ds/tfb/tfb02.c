/*
 *  FILE %ds/tfb/tfb02.c
 *
 *  written:       1994-05-10
 *  latest update: 1995-11-11
 *  $Id: tfb02.c,v 1.2 2001/12/19 08:07:45 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/sbr.h>
#include <gg/tfb.h>
#include <gg/diagnose.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int tfb_get_2entry (
char *keyword,
char *file_tfb,
char *lut_buffer,
char *line_buffer,
int MAX_LINE_BUFFER)
{
  FILE *fi;
  long pos;
  int rc;
  int lng;

  if (lut_buffer == (char *) 0)
  {
    gg_diagnose= TFB_ge_no_lut;
    return -1;
  }

  rc= lookup_char (lut_buffer, keyword, &pos, &lng);
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
