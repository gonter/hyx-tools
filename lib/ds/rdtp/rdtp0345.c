/*
 *  $Id: rdtp0345.c,v 1.3 2000/06/05 17:04:56 gonter Exp $
 *  FILE %ds/rdtp/rdtp0345.c
 *
 *  restructured dynamic text parser
 *  destroy a complete tag structure
 *
 *  written:       1997-06-16
 *  latest update: 2000-06-05 18:43:13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/rdtp.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_destroy_tag (struct SGML_OPENING_TAG *ot)
{
  struct SGML_ATTRIBUTE_LIST *av, *av_next;

  if (ot == (struct SGML_OPENING_TAG *) 0) return -1;

  for (av= ot->attributes;
       av != (struct SGML_ATTRIBUTE_LIST *) 0;
      )
  {
    av_next= av->next;
    sgml_destroy_attribute (av);
    av= av_next;
  }

  free (ot);

  return 0;
}
