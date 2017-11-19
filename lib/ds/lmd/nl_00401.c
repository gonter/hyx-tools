/*
 *  FILE %ds/lmd/nl_00401.c
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
 *  latest update: 1996-12-22 17:41:34
 *
 */

#include <string.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_score (
struct LMDC_CONTROL *lmdc,
char *s,                /* word to be placed in lookup table                */
long cnt,               /* counter or code                                  */
int mode)               /* bit 0 .. set counter to this value               */
                        /* bit 1 .. record code in word number field        */
{
  struct YTREE *p;

  if (nl_key_valid (s) == -1) return -1;
  if ((p= ytree_insert_word (&lmdc->LMDC_ytree, (unsigned char *) s))
      == (struct YTREE *) 0)
  {
    lmd_error04 ("Out of Memory");
    return -1;
  }

  p->YT_flags |= YTflag_EOW;

  if (mode & 0x0001)
       p->YT_info += cnt;
  else p->YT_info  = cnt;

  return 0;
}
