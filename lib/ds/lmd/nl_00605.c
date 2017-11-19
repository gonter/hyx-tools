/*
 *  FILE %nl_kr/lib/nl_00605.c
 *
 *  read and process a text file
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1995-12-05
 *  $Id: nl_00605.c,v 1.2 2001/10/08 15:01:26 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
long lmd_veronica_process (
struct LMDC_CONTROL *lmdc,
char *fn,
int *alphabet)
{
  FILE *fi;
  int ls;
#define N_FIELDS 20
  char *fields [N_FIELDS];
  char *w1;
#define N_WORDS 40              /* maximum number of isolated words on line */
  char *words [N_WORDS];        /* isolated words                           */
  char *wrd;                    /* currently processed word                 */
  int fc;
  int wc;
  long pos= 0L;
  int i;
  int ll;
  int min_wordlength;
  int max_wordlength;
  long word_count= 0L;
  char *str1;
  int MAX_STR;
  char docid_str [10];

  if (lmdc == (struct LMDC_CONTROL *) 0
      || (str1= lmdc->LMDC_buffer1) == (char *) 0
     ) return -1L;

  if ((fi= fopen (fn, "r")) == (FILE *) 0)
  {
    fprintf (stderr, "can't read veronica directory %s\n", fn);
    return -1L;
  }

  MAX_STR= lmdc->LMDC_buffer_size;
  min_wordlength= lmdc->LMDC_min_wordlength;
  max_wordlength= lmdc->LMDC_max_wordlength;

  for (;;)
  {
    ls= fread_line (fi, str1, MAX_STR);
    if (ls <= 0L && feof (fi)) break;

/* printf ("line=%s\n", line); */
    if (str1 [0] == 'i') goto NEXT; /* no info items */

    fc= split_string (str1, '\t', fields, N_FIELDS);
    if (fc < 4) continue;
    w1= &str1[1];
    wc= isolate2words (w1, words, N_WORDS, alphabet);
    if (wc > N_WORDS) wc= N_WORDS;

    pos++;   
    long_to_hex (pos, docid_str);
    for (i= 0; i<wc; i++)
    {
      wrd= words [i];
      to_lower (wrd);
/* printf ("  word=%s\n", wrd); */
      ll= strlen (wrd);
      if (ll < min_wordlength) continue;
      if (ll > max_wordlength) wrd [max_wordlength]= 0;
      lmd_idx (lmdc, wrd, pos, -1L, docid_str, 0, 0, 0L);
      word_count++;
    }

NEXT:
    pos= ftell (fi);
  }

  fclose (fi);

  return word_count;
}
