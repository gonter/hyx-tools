/*
 *  FILE %nl_kr/lib/nl_00135.c
 *
 *
 *  written:       1995-07-30
 *  latest update: 1995-12-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_qs_setup_table_names (struct LMD_QUERY_SET *lmdqs, char *s)
{
  str_assign (&lmdqs->LMDQS_fn_lut, s);
     fnmcpy3 (&lmdqs->LMDQS_fn_wr,  s, ".wr");
     fnmcpy3 (&lmdqs->LMDQS_fn_di,  s, ".di");

  return 0;
}
