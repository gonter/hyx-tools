/*
 *  FILE %ds/rdtp/rdtp0302.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1996-09-14 22:21:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_nop (struct RDTP_THREAD *thr, int ch)
{
#ifdef MSDOS
  thr;
  ch;
#endif

  return 0;
}
