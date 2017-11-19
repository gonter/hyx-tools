/*
 *  FILE %ds/rdtp/rdtp0314.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-23
 *  latest update: 1996-09-15 10:20:39
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
int sgml_new_element (struct RDTP_THREAD *thr, int ch)
{
  struct SGML_BUILDUP *rtf;

#ifdef MSDOS
  ch;
#endif

  if (thr == (struct RDTP_THREAD *) 0
      || (rtf= (struct SGML_BUILDUP *) thr->payload)
         == (struct SGML_BUILDUP *) 0
     )
  {
    fprintf (stderr, "rdtp0305: bad thread\n");
    return -1;
  }

  sgml_flush_buffer (rtf);

  /* T2D */

  return 0;
}
