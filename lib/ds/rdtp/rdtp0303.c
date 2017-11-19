/*
 *  FILE %ds/rdtp/rdtp0303.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1997-06-17 14:07:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_error (void *thrp, int ch)
{
  struct RDTP_THREAD *thr;

  if ((thr= (struct RDTP_THREAD *) thrp) == (struct RDTP_THREAD *) 0)
     return -1;

  printf (
    "sgml_error: undefined state (processing 0x%02x), resetting to start!\n",
    ch);

  thr->current_state= thr->class->start_state;

  return 0;
}
