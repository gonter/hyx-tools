/*
 *  FILE ~/usr/nl_kr/lib/nl_00137.c
 *
 *  deref a word
 *
 *  written:       1995-07-30
 *  latest update: 1995-07-30
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_deref_finish (struct LMD_QUERY_SET *lmdqs)
{
  if (!lmdqs->LMDQS_initialized) return -1;

  fclose (lmdqs->LMDQS_F_lt);
  fclose (lmdqs->LMDQS_F_wr);
  fclose (lmdqs->LMDQS_F_di);

  lmdqs->LMDQS_F_lt= (FILE *) 0;
  lmdqs->LMDQS_F_wr= (FILE *) 0;
  lmdqs->LMDQS_F_di= (FILE *) 0;

  lmdqs->LMDQS_initialized= 0;

  return 0;
}
