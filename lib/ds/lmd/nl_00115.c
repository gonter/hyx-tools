/*
 *  FILE ~/usr/nl_kr/lib/nl_00115.c
 *
 *  seek word ref information by index
 *
 *  written:       1994-07-31: isolated from nl_00114.c
 *  latest update: 1995-07-30
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_find_word_ref (
FILE *f_wr,
long w_info,
struct WORD_REF *wr)
{
  long pos;

  pos= WORD_REF_SIZE * w_info;

#ifdef DEBUG
printf ("nl_00115: w_info=0x%08lX, pos=0x%08lX\n", w_info, pos);
#endif /* DEBUG */

  fseek (f_wr, pos, 0);
  if (lmd_read_word_ref (f_wr, wr) != 1) return -1;

  return 0;
}
