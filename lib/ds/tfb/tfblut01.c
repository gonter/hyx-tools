/*
 *  FILE %ds/tfb/tfblut01.c
 *
 *  generate lut_file for a tfb file
 *
 *  written:       1993-10-19
 *  latest update: 1997-10-06 13:23:03
 *  $Id: tfblut01.c,v 1.3 2002/07/17 07:04:35 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/tfb.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
#define MAX_LINE        4096
#define MAX_FIELDS      1024

static char line [MAX_LINE];
static char *fields [MAX_FIELDS];

static struct YTREE *ytree= (struct YTREE *) 0;
extern long YTREE_ALLOCATED;
extern long YTREE_ALLOC_SIZE;
extern long YTREE_truncated;

/* ------------------------------------------------------------------------ */
int tfb_make_lut_file (
char *tfb_file,
char *lut_file,
int field_number,
int field_delimiter,
int open_quote,
int close_quote,
int escape_char,
int ambigous_key,
int modification,
int truncation,
int verbosity,
int use_pos)          /* field number to be used instead of pos */
{
  FILE *fi;
  int rc;
  int fc;
  long line_number= 0;
  long cnt_used= 0L;
  long cnt_unique;
  long cnt_bytes;
  struct YTREE *yt;
  char *indexed_field= (char *) 0;
#define MAX_REC_ID 24
  char REC_ID [MAX_REC_ID];
  long pos;
  long rec_id_code;
  int rec_id_fmt;
  char *rec_id_fmt_str;
  int i;
  int j;

  if ((fi= fopen (tfb_file, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "tfb_make_lut_file: couldn't open %s\n", tfb_file);
    return -1;
  }

  fseek (fi, 0L, 0);
  for (;;)
  {
    pos= ftell (fi);
    rc= fread_line (fi, line, MAX_LINE);
    if (rc <= 0 && feof (fi)) break;
    line_number++;
    if (line [0] == '#') continue;

    if (field_number < 0)
    {
      switch (field_number)
      {
        default:
          rec_id_code= line_number;
          rec_id_fmt= 0;
          break;

        case -2:
          rec_id_code= line_number;
          rec_id_fmt= 1;
          break;

        case -3:
          rec_id_code= line_number;
          rec_id_fmt= 3;
          break;

        case -4:
          rec_id_code= line_number;
          rec_id_fmt= 4;
          break;

        case -5:
          rec_id_code= pos;
          rec_id_fmt= 0;
          break;

        case -6:
          rec_id_code= pos;
          rec_id_fmt= 1;
          break;

        case -7:
          rec_id_code= pos;
          rec_id_fmt= 3;
          break;

        case -8:
          rec_id_code= pos;
          rec_id_fmt= 4;
          break;

      }

      switch (rec_id_fmt)
      {
        default: rec_id_fmt_str= "%ld"; break;
        case 1:  rec_id_fmt_str= "%08ld"; break;
        case 2:  rec_id_fmt_str= "%lX"; break;
        case 3:  rec_id_fmt_str= "%08lX"; break;
      }
      sprintf (REC_ID, rec_id_fmt_str, rec_id_code);
      goto INSERT;
    }

    fc= str2fld (line, fields, MAX_FIELDS,
                 field_delimiter, open_quote, close_quote, escape_char);

    switch (verbosity)
    {
      case 2:
        printf ("%d fields identified:\n", fc);
        if ((j= fc) > MAX_FIELDS) j= MAX_FIELDS;
        for (i= 0; i < j; i++) printf ("[%d] '%s'\n", i, fields [i]);
        break;
    }

    if (use_pos >= 0
        && use_pos < fc
        && (indexed_field= fields [use_pos]) != (char *) 0
        && *indexed_field != 0
       )
    {
      pos= get_parameter_value (indexed_field);
/**** printf ("modified pos=%ld\n", pos); ****/
    }
    else { pos++; }

    if (field_number >= 0
        && field_number < fc
        && (indexed_field= fields [field_number]) != (char *) 0
        && *indexed_field != 0
       )
    {
      switch (modification)
      {
        case MK_tolower: to_lower (indexed_field); break;
        case MK_toupper: to_upper (indexed_field); break;
      }

      if (truncation > 0 && strlen (indexed_field) > truncation)
        indexed_field [truncation]= 0;

INSERT:
      /* printf ("indexed_field= %s\n", indexed_field); */
      if ((yt= ytree_insert_word (&ytree,
                                  (unsigned char *) indexed_field))
          == (struct YTREE *) 0)
      {
        fprintf (stderr,
                 "tfb_make_lut_file: %s(%ld) can't insert '%s'\n",
                 tfb_file, line_number, indexed_field);
        fprintf (stderr,
                 "%ld ytree nodes; %ld bytes total size; %ld wasted\n",
                 YTREE_ALLOCATED, YTREE_ALLOC_SIZE, YTREE_truncated);

        goto DONE;
      }
      else
      {
        if (yt->YT_flags & YTflag_EOW)
        {
          if (verbosity == 2) printf ("already present\n");
          if (ambigous_key & AK_complain)
            printf ("tfb_make_lut_file: %s(%ld) duplicate key '%s'\n",
                    tfb_file, line_number, indexed_field);

          if (ambigous_key & AK_last)
            goto USE;
        }
        else
        {
          if (verbosity == 2) printf ("new\n");
          cnt_used++;
USE:
          yt->YT_flags |= YTflag_EOW;
          yt->YT_info= pos;
        }
      }
    }
  }

DONE:
  fclose (fi);

  if ((fi= fopen (lut_file, "wb")) == (FILE *) 0)
  {
    fprintf (stderr, "tfb_make_lut_file: couldn't open %s\n", lut_file);
    return -1;
  }

  cnt_bytes= ytree_size (ytree);
  cnt_unique= ytree_dump (fi, ytree);
  fclose (fi);

  printf ("tfb_make_lut_file: fnm=%s lines=%ld used=%ld unique=%ld\n",
          tfb_file, line_number, cnt_used, cnt_unique);
  printf ("tfb_make_lut_file: lut=%s bytes=%ld\n",
          lut_file, cnt_bytes);

  return 0;
}
