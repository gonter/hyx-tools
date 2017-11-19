/*
 *  FILE %nl_kr/lib/nl_00606.c
 *
 *  read and process a text file
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1995-12-05
 *  $Id: nl_00606.c,v 1.2 2001/10/08 15:01:26 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
long lmd_read_tfb (
struct LMDC_CONTROL *lmdc,
char *fn,
int position,
int TFB_delimiter,
int *alphabet)
{
  FILE *fi;
  int ls;
#define N_FIELDS 20
  char *fields [N_FIELDS];
  char *w1;
#define N_WORDS 40
  char *words [N_WORDS];
  char *wrd;
  int fc;
  int wc;
  long pos= 0L;
  int i;
  int ll;
  int min_wordlength;
  int max_wordlength;
  char *str1;
  int MAX_STR;
  long word_count= 0L;
  char docid_str [10];
  int rc;

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (str1= lmdc->LMDC_buffer1) == (char *) 0
     ) return -1L;

  MAX_STR= lmdc->LMDC_buffer_size;
  min_wordlength= lmdc->LMDC_min_wordlength;
  max_wordlength= lmdc->LMDC_max_wordlength;

  if ((fi= fopen (fn, "r")) == (FILE *) 0)
  {
    fprintf (stderr, "can't read tfb file %s\n", fn);
    return -1L;
  }

  for (;;)
  {
    ls= fread_line (fi, str1, MAX_STR);
    if (ls <= 0L && feof (fi)) break;
/* printf ("line=%s\n", line); */

    if ((fc= split_string (str1, TFB_delimiter, fields, N_FIELDS)) < 1)
       continue;

    w1= fields [position];
    if ((wc= isolate2words (w1, words, N_WORDS, alphabet)) > N_WORDS)
      wc= N_WORDS;

    pos++;
    long_to_hex (pos, docid_str);
    for (i= 0; i < wc; i++)
    {
      wrd= words [i];
      ll= strlen (wrd);
      if (ll < min_wordlength) continue;
      if (ll > max_wordlength) wrd [max_wordlength]= 0;
      to_lower (wrd);

      rc= lmd_idx (lmdc, wrd, pos, -1L, docid_str, 0, 0, 0L);
      if (rc == 0) word_count++;
    }

    pos= ftell (fi);
  }

  fclose (fi);

  return word_count;
}
