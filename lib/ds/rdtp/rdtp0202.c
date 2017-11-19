/*
 *  FILE %ds/rdtp/rdtp0202.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-04-02
 *  latest update: 1997-01-15 10:48:51
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp02.h>

/* ------------------------------------------------------------------------ */
int rtf_nop (void *thrp, int ch)
{
#ifdef MSDOS
  thrp;
  ch;
#endif

  return 0;
}
