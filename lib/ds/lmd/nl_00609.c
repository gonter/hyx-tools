/*
 *  FILE ~/usr/nl_kr/lib/nl_00609.c
 *
 *  read and process a text file
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1995-07-09
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
/* Frequency table einlesen */
long lmd_read_long_fcy (
struct LMDC_CONTROL *lmdc,
char *fn)
{
  FILE *fi;
  long fcy;
  char *line;
  int MAX_STR;
  int rc;
  long word_count= 0L;
  char *fields [2];

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (line= lmdc->LMDC_buffer1) == (char *) 0) return -1L;

  MAX_STR= lmdc->LMDC_buffer_size;

  if ((fi= fopen (fn, "rt")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -1L;
  }

  for (;;)
  {
    rc= fread_line (fi, line, MAX_STR);
    if (rc <= 0 && feof (fi)) break;
    if (isolate_tokens (line, fields, 2) < 2) continue;
    fcy= get_parameter_value (fields [0]);

    lmd_SWT (lmdc, fields [1], fcy);
    word_count += fcy;
  }
  fclose (fi);

  return word_count;
}
