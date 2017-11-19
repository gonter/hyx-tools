/*
 *  FILE %ds/lmd/nl_00602.c
 *
 *  read and process a text file
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1996-12-22 13:02:48
 *  $Id: nl_00602.c,v 1.2 2001/08/26 23:26:04 gonter Exp $
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
long lmd_read_tokens (
struct LMDC_CONTROL *lmdc,
char *fn,
long docid,
char *docid_str,
long f_from,
long f_size,
long f_end,
int verbosity)
{
  FILE *fi;
  int rv;
  int ll;
  int push= 0;
  long pos= 0L;
  long byr;
  long word_count= 0L;
  int min_wordlength;
  int max_wordlength;
  char *line;

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (line= lmdc->LMDC_buffer1) == (char *) 0
     ) return -1L;

  min_wordlength= lmdc->LMDC_min_wordlength;
  max_wordlength= lmdc->LMDC_max_wordlength;

  if ((fi= fopen (fn, "r")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -1L;
  }

  fseek (fi, f_from, 0);
  if (f_end <= 0L && f_size <= 0L) f_end= 0x7FFFFFFFL;
  else if (f_end <= 0L) f_end= f_from+f_size;

  if (verbosity)
    fprintf (stderr, "reading tokens from %s, docid=%ld %ld-%ld\n",
             fn, docid, f_from, f_end);

  while (pos < f_end)
  {
    byr= pos;
    rv= nl_get_token (fi, line, 0x002F, &push, &pos);

    byr= pos-byr;
    total_bytes_read += byr;
    if (rv == 0 || pos >= f_end) break;

    if (rv & 0x0003)
    {
      to_lower (line);
      /* printf ("%02X %s\n", rv, line); */
      ll= strlen (line);
      if (ll < min_wordlength) continue;
      if (ll > max_wordlength) line [max_wordlength]= 0;
      lmd_idx (lmdc, line, docid, -1L, docid_str, 0, 0, pos);
    }
    word_count++;
  }
  fclose (fi);

/* ANM: ******************************************************************* */
/* 0x002F bei nl_get_token: Wort bestehend aus Buchstaben, Ziffern,         */
/*                          nationalen Sonderzeichen, Symbolen, Underliner. */
/* 0x0003 bei if ( ) SW( ): Wort muss zumindestens einen Buchstaben oder    */
/*                          Ziffer haben, um gescort werden zu koennen.     */
/* ************************************************************************ */

  return word_count;
}
