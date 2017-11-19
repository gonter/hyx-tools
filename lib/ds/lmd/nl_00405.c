/*
 *  FILE %ds/lmd/nl_00405.c
 *
 *  data
 *  - functions to create LUTs -- using YTREE
 *  - see also: wordcr05.c (word reference system)
 *
 *  written:       1990 06 04
 *                 1990 11 16: revision
 *                 1991 03 16: revision; AIX
 *                 1993-02-28: complete redesign of the refenece system
 *                 1994-12-19: isolated from wordcr04.c
 *  latest update: 1996-12-22 17:42:14
 *
 */

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
static int kill_id_cnt= 0;
static int kill_word_cnt= 0;
static long  kill_ids[]= { 0L };
static char *kill_words[]= { "" } ;

/* ------------------------------------------------------------------------ */
int lmd_RL4 (
struct LMDC_CONTROL *lmdc,
char *LUT_in)                   /* Name des Files mit LUT (Binaer)          */
{
  FILE *fi;
  int rc;

  if ((fi= fopen (LUT_in, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "can't open %s to read LUT!\n", LUT_in);
    return -1;
  }

  rc= ytree_full_scan (fi, &lmdc->LMDC_ytree,
                       kill_ids, kill_id_cnt,
                       kill_words, kill_word_cnt);

  fclose (fi);

  return rc;
}
