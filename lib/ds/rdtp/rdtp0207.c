/*
 *  FILE %ds/rdtp/rdtp0207.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1997-06-17 14:14:26
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
int rtf_print_statistics (struct RDTP_THREAD *thr)
{
  struct RTF_BUILDUP *rtf;

  if (thr == (struct RDTP_THREAD *) 0
      || (rtf= (struct RTF_BUILDUP *) thr->payload)
               == (struct RTF_BUILDUP *) 0
     )
  {
    fprintf (stderr, "rdtp0205: bad thread!\n");
    return -1;
  }

  ytree_process_info (rtf->names, rtf_print_name_statistics, (void *) 0);

  return 0;
}
