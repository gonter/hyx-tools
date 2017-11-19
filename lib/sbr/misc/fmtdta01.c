/*
 *  FILE %sbr/fmtdta01.c
 *
 *  written:       1994-02-12
 *  latest update: 1996-07-19 18:46:00
 *
 */

#include <stdio.h>
#include <gg/filename.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
int fmt_dta_date (char *puffer, int fn_date)
{
  sprintf (puffer,
           "%04d-%02d-%02d",
           ((fn_date >>  9) & 0x7F) + 1980,
            (fn_date >>  5) & 0x0F,
             fn_date        & 0x1F);

  return 0;
}
