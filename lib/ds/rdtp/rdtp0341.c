/*
 *  FILE %ds/rdtp/rdtp0341.c
 *
 *  restructured dynamic text parser
 *  create a new opening tag structure
 *
 *  written:       1997-06-16
 *  latest update: 1997-06-16 17:23:40
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
struct SGML_OPENING_TAG *sgml_new_opening_tag (
struct SGML_BUILDUP *ctx,
char *name)
{
  struct SGML_OPENING_TAG *ot;
  struct SGML_TAG_NAME *element_name;

  if (ctx == (struct SGML_BUILDUP *) 0
      || (element_name= sgml_add_element (ctx, name))
          == (struct SGML_TAG_NAME *) 0
      || (ot= (struct SGML_OPENING_TAG *)
              calloc (sizeof (struct SGML_OPENING_TAG), 1))
          == (struct SGML_OPENING_TAG *) 0
     ) return  (struct SGML_OPENING_TAG *) 0;

  ot->tag_name= element_name;
  ot->attr_append= &ot->attributes;

  return ot;
}
