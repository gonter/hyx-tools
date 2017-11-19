/*
 *  FILE %ds/rdtp/rdtp0347.c
 *
 *  restructured dynamic text parser
 *  transform a tag structure to a string
 *
 *  written:       1997-06-16
 *  latest update: 1997-06-16 19:06:26
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
int sgml_space_required (struct SGML_OPENING_TAG *ot)
{
  struct SGML_ATTRIBUTE_LIST *av;
  struct SGML_TAG_NAME *tn;
  char *name;
  char *cp;
  int size= 0;

  if (ot == (struct SGML_OPENING_TAG *) 0
      || (tn= ot->tag_name) == (struct SGML_TAG_NAME *) 0
      || (name= tn->tag_name) == (char *) 0
     )
  {
    return -1;
  }

  size= 2+strlen (name);

  for (av= ot->attributes;
       av != (struct SGML_ATTRIBUTE_LIST *) 0;
       av= av->next
      )
  {
    size++; /* space between two attribute pairs */

    if ((cp= av->attribute_name) != (char *) 0)
    {
      size += 1 + strlen (cp);          /* = char */
    }

    if ((cp= av->attribute_value) != (char *) 0)
    {
      size += 2 + strlen (cp);          /* 2x quote */
    }
  }

  return size;
}
