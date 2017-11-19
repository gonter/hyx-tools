/*
 *  FILE %ds/lmd/nl_00608.c
 *
 *  read and process a text file
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1996-03-17 19:39:18
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
/* read frequency table */
long lmd_read_fcy (
struct LMDC_CONTROL *lmdc,
char *fn)
{
  FILE *fi;
  int v1, v2;
  char *line;
  long word_count= 0L;

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (line= lmdc->LMDC_buffer1) == (char *) 0
     ) return -1L;

  if ((fi= fopen (fn, "rt")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -1L;
  }

  for (;;)
  {
    fscanf (fi, "%d%d%s", &v1, &v2, line);
    if (feof (fi)) break;

    lmd_SWX (lmdc, line, ((long) v1) + (((long) v2)*0x10000L));
    word_count += v1;
  }
  fclose (fi);

  return word_count;
}
