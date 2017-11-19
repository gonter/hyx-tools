/*
 *  FILE %ds/rdtp/rdtp0309.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1997-06-16 13:57:09
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
int sgml_element_name_end (void *thrp, int ch)
{
  struct RDTP_THREAD *thr;
  struct SGML_BUILDUP *sb;
  char *element;

  if ((thr= (struct RDTP_THREAD *) thrp) == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
          == (struct SGML_BUILDUP *) 0
     )
  {
    rdtp_bad_thread ("rdtp0309");
    return -1;
  }

#ifdef MSDOS
  ch;
#endif

  sb->bl1 [sb->bl1_cnt]= 0;
  sb->bl1_cnt= 0;
  element= sb->bl1;

  return (sgml_add_element (sb, element) == (struct SGML_TAG_NAME *) 0)
         ? -1 : 0;
}
