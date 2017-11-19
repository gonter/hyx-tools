/*
 *  FILE %ds/lmd/nl_00404.c
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
 *  latest update: 1996-12-22 17:42:22
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
long lmd_PL (
struct YTREE *yt,
char *LUT_out,          /* Name des Files mit LUT (Binaer)                  */
char *TABLE_out)        /* .    .   .     .   Woerterbuch (ASCII)           */
/* return: number of entries in the lut dumped, if any                      */
{
  FILE *fo;
  long word_cnt= 0L;

  ytree_size (yt);
  if (LUT_out != (char *) 0 && *LUT_out)
  {
    if (strcmp (LUT_out, "-") == 0)
    {
      word_cnt= ytree_dump (stdout, yt);
    }
    else
    {
      if ((fo= fopen (LUT_out, "wb")) == (FILE *) 0)
      {
        fprintf (stderr, "can't open %s to write LUT!\n", LUT_out);
        return -1;
      }
      word_cnt= ytree_dump (fo, yt);
      fclose (fo);
    }
  }

  if (TABLE_out != (char *) 0 && *TABLE_out)
  {
    if (strcmp (TABLE_out, "-") == 0)
    {
      ytree_print (stdout, yt, 0);
    }
    else
    {
      if ((fo= fopen (TABLE_out, "wt")) == (FILE *) 0)
      {
        fprintf (stderr, "can't open %s to write ytree-info!\n", TABLE_out);
        return -1;
      }

      ytree_print (fo, yt, 0);
      fclose (fo);
    }
  }

  return word_cnt;
}
