/*
 *  FILE %sbr/fmtdta02.c
 *
 *  written:       1994-02-12
 *  latest update: 1996-07-19 18:46:46
 *
 */

#include <stdio.h>
#include <gg/filename.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
int fmt_dta_time (char *puffer, int fn_time)
{
  sprintf (puffer,
           "%02d:%02d:%02d",
           (fn_time >> 11) & 0x1F,
           (fn_time >>  5) & 0x3F,
           (fn_time        & 0x1F) << 1);

  return 0;
}
