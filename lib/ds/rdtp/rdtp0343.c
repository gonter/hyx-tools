/*
 *  FILE %ds/rdtp/rdtp0343.c
 *
 *  restructured dynamic text parser
 *  print tag complete with attributes
 *
 *  written:       1997-06-16
 *  latest update: 1997-06-16 17:23:33
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
int sgml_diag_tag (
FILE *fo,
struct SGML_OPENING_TAG *ot)
{
  struct SGML_ATTRIBUTE_LIST *av;
  struct SGML_TAG_NAME *tn;
  char *name;
  char *cp;

  fputs ("tag: ", fo);
  if (ot == (struct SGML_OPENING_TAG *) 0
      || (tn= ot->tag_name) == (struct SGML_TAG_NAME *) 0
      || (name= tn->tag_name) == (char *) 0
     )
  {
    fputs ("<NULL>\n", fo);
    return 0;
  }

  fputs (name, fo);
  fputc ('\n', fo);

  for (av= ot->attributes;
       av != (struct SGML_ATTRIBUTE_LIST *) 0;
       av= av->next
      )
  {
    if ((cp= av->attribute_name) != (char *) 0)
      fprintf (fo, "  %s=\"", cp);
    if ((cp= av->attribute_value) != (char *) 0)
    {
      fputs (cp, fo);
      fputc ('\"', fo);
    }
    fputc ('\n', fo);
  }

  return 0;
}
