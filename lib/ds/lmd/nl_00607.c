/*
 *  FILE %ds/lmd/nl_00607.c
 *
 *  read and process a text file
 *
 *  ** OBSOLETE **
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1996-12-22 13:59:04
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
static long total_bytes_read= 0L;

/* ------------------------------------------------------------------------ */
long lmd_read_words (
struct LMDC_CONTROL *lmdc,
char *fn)
{
  FILE *fi;
  int ll;
  int min_wordlength;
  int max_wordlength;
  char *line;
  int MAX_STR;
  long word_count= 0L;

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (line= lmdc->LMDC_buffer1) == (char *) 0) return -1L;

  MAX_STR= lmdc->LMDC_buffer_size;
  min_wordlength= lmdc->LMDC_min_wordlength;
  max_wordlength= lmdc->LMDC_max_wordlength;

  if ((fi= fopen (fn, "r")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -1L;
  }

  for (;;)
  {
    total_bytes_read += (long) nl_get_str (fi, line);
    if (feof (fi)) break;

    ll= strlen (line);
    if (ll < min_wordlength) continue;
    if (ll > max_wordlength) line [max_wordlength]= 0;
    to_lower (line);

    lmd_SW (lmdc, line);
    word_count++;
  }
  fclose (fi);

  return word_count;
}
