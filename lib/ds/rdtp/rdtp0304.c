/*
 *  FILE %ds/rdtp/rdtp0304.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1997-01-15 11:19:13
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
int sgml_name_begin (void *thrp, int ch)
{
  struct SGML_BUILDUP *sb;
  struct RDTP_THREAD *thr;

  if ((thr= (struct RDTP_THREAD *) thrp) == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
         == (struct SGML_BUILDUP *) 0
     )
  {
    fprintf (stderr, "rdtp0304: bad thread\n");
    return -1;
  }

  sb->bl1 [0]= (char) ch;
  sb->bl1_cnt= 1;

  return 0;
}
