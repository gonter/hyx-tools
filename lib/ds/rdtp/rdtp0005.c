/*
 *  FILE %ds/rdtp/rdtp0005.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-09-15
 *  latest update: 1996-09-15  9:54:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>

/* ------------------------------------------------------------------------ */
void rdtp_bad_thread (char *id)
{
  fputs (id, stderr);
  fputs (": bad thread\n", stderr);
}
