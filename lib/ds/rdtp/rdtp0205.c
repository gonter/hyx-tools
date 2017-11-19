/*
 *  FILE %ds/rdtp/rdtp0205.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1997-01-15 10:51:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp02.h>

/* ------------------------------------------------------------------------ */
int rtf_cmd_name (void *thrp, int ch)
{
  struct RTF_BUILDUP *rtf;
  struct RDTP_THREAD *thr;

  if ((thr= (struct RDTP_THREAD *) thrp) == (struct RDTP_THREAD *) 0
      || (rtf= thr->payload) == (struct RTF_BUILDUP *) 0
     )
  {
    fprintf (stderr, "rdtp0204: bad thread\n");
    return -1;
  }

  if (rtf->bl1_cnt < TMP_BL_SIZE -1)
    rtf->bl1 [rtf->bl1_cnt++]= (char) ch;

  return 0;
}
