/*
 *  FILE %ds/lmd/nl_01001.c
 *
 *  written:       1991 02 16
 *  latest update: 1997-08-28 13:23:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct FCY
{
  struct FCY *next;
  long freq;
  char w[2];
} ;

/* ------------------------------------------------------------------------ */
static struct FCY *fcy_list= (void *) 0;

static long total_words= 0L;
static long total_unique= 0L;

/* ------------------------------------------------------------------------ */
int sort_by_frequency (char *wort, long frequency)
{
  struct FCY *fl;
  struct FCY **flp;

  total_words += frequency;

  /* 1. gleiche Worte aufsuchen */
#ifdef NOT_USED
  for (flp = &fcy_list; (fl = *flp) != (void *) 0; flp = &fl->next)
    if (strcmp (fl->w, wort) == 0)
    {
      fl->freq += frequency;
      return 0;
    }
#endif

  /* 2. einsortieren nach Frequenz */
  for (flp = &fcy_list; (fl = *flp) != (void *) 0; flp = &fl->next)
    if (fl->freq < frequency
        || (fl->freq == frequency
            && strcmp (fl->w, wort) > 0)) break;

  /* Wort nicht gefunden -> hinten an die Liste anfuegen */
  fl = malloc (sizeof (struct FCY) + strlen (wort)-1);
  fl->next = *flp;
  fl->freq = frequency;
  strcpy (fl->w, wort);
  *flp = fl;
  total_unique++;

  return 0;
}

/* ------------------------------------------------------------------------ */
int print_sorted (FILE *fo)
{
  struct FCY *fl;
  long wc=0L;
  long fcy=0L;
  long fcy_acc=0L;
  double pct;
  double pct_acc;

  fprintf (fo, "rank (pct) freq.   (pct)  accum. word\n");
  for (fl = fcy_list; fl != (void *) 0; fl = fl->next)
  {
    wc++;
#ifdef JUNK
    if (fcy != fl->freq)
         {
#endif
           fcy = fl->freq;
           pct = (double) (fcy*100L);
           pct = pct / (double) total_words;
           fprintf (fo, "%4ld %3ld%% %6ld %6.2f%% ",
                    wc, wc*100L/total_unique, fcy, pct);
#ifdef JUNK
         }
    else {
           fprintf (fo, "                        ");
         }
#endif

    fcy_acc += fcy;
    pct_acc = (double) (fcy_acc*100L);
    pct_acc = pct_acc / (double) total_words;
    fprintf (fo, "%6.2f%% %s\n", pct_acc, fl->w);
  }
  return 0;
}
