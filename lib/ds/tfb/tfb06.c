/*
 *  FILE %ds/tfb/tfb06.c
 *
 *  written:       1996-05-24
 *  latest update: 1997-08-28 13:29:11
 *  $Id: tfb06.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/strings.h>
#include <gg/sbr.h>
#include <gg/tfb.h>
#include <gg/diagnose.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int tfb_get_tag_entry (
const char *keyword,
const char *file_tfb,
const char *file_lut,
char *line_buffer,
char **field_fnm,
char **field_location,
int MAX_LINE_BUFFER,
int kw_lng)                     /* significant length of keyword            */
{
  FILE *fi;
  long pos= -1;
  int rc;
  int sc;
  int lng;
  struct stat st_tfb;
  struct stat st_lut;
  char *fields [3];

  if (stat (file_tfb, &st_tfb) != 0
      || field_fnm      == (char **) 0
      || field_location == (char **) 0
     ) return -1;

  if (stat (file_lut, &st_lut) == 0
      && st_lut.st_mtime >= st_tfb.st_mtime
      && (fi= fopen (file_lut, "rb")) != (FILE *) 0
     )
  {
    rc= lookup_file (fi, keyword, &pos, &lng);
    fclose (fi);
    if (!(rc & LOOKUP_found)) pos= -1;
  }

  if ((fi= fopen (file_tfb, "rb")) == (FILE *) 0)
  {
    gg_diagnose= TFB_ge_no_tfb;
    return -1;
  }

  if (pos > 0L) fseek (fi, pos-1L, 0);
  for (;;)
  {
    rc= fread_line (fi, line_buffer, MAX_LINE_BUFFER);
    if (rc <= 0 && feof (fi))
    {
      rc= -1;
      break;
    }

    if (line_buffer [0] == '#') continue;
    sc= split_string (line_buffer, '\t', fields, 3);
    if (sc >= 3
        && ((kw_lng == 0 && strcmp (fields [0], keyword) == 0)
            || (kw_lng > 0 && strncmp (fields [0], keyword, kw_lng) == 0)
           )
       )
    {
      *field_fnm=      fields [1];
      *field_location= fields [2];
      rc= 1;
      break;
    }

    if (pos > 0L)
    {
      rc= -1;
      break;
    }
  }

  fclose (fi);

  if (rc <= 0)
  {
    gg_diagnose= TFB_ge_tfb_bad;
    return -1;
  }

  return 1;
}
