/*
 *  FILE ~/usr/nl_kr/lib/nl_00136.c
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
int lmd_deref_init (struct LMD_QUERY_SET *lmdqs)
{
#ifdef DEBUG
  fprintf (stderr, "query set: lt=%s wr=%s di=%s\n",
           lmdqs->LMDQS_fn_lut, lmdqs->LMDQS_fn_wr, lmdqs->LMDQS_fn_di);
#endif

  if ( (lmdqs->LMDQS_F_lt= fopen (lmdqs->LMDQS_fn_lut, "rb")) == (FILE *) 0
     ||(lmdqs->LMDQS_F_wr= fopen (lmdqs->LMDQS_fn_wr,  "rb")) == (FILE *) 0
     ||(lmdqs->LMDQS_F_di= fopen (lmdqs->LMDQS_fn_di,  "rb")) == (FILE *) 0 )
    return -1;

  lmdqs->LMDQS_initialized= 1;

  return 0;
}
