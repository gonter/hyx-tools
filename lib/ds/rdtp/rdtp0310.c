/*
 *  FILE %ds/rdtp/rdtp0310.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1996-09-14 22:30:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_entity_name_end (struct RDTP_THREAD *thr, int ch)
{
  struct SGML_BUILDUP *rtf;

  if (thr == (struct RDTP_THREAD *) 0
      || (rtf= (struct SGML_BUILDUP *) thr->payload)
         == (struct SGML_BUILDUP *) 0
     )
  {
    fprintf (stderr, "rdtp0204: bad thread\n");
    return -1;
  }

  return sgml_name_end (rtf, ch, &rtf->entity_names);
}
