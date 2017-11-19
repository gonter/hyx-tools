/*
 *  $Id: rdtp0342.c,v 1.4 2000/06/05 17:05:13 gonter Exp $
 *  FILE %ds/rdtp/rdtp0342.c
 *
 *  restructured dynamic text parser
 *  add a attribute name/value pair to a tag's structure
 *
 *  written:       1997-06-16
 *  latest update: 2000-06-05 18:27:21
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
struct SGML_ATTRIBUTE_LIST *sgml_add_attribute (
struct SGML_OPENING_TAG *ot,
char *name,
char *value)
{
  struct SGML_ATTRIBUTE_LIST *av;
  char *cp;
  int ch;
  int flg= 0x00;

  if (ot == (struct SGML_OPENING_TAG *) 0
      || (av= (struct SGML_ATTRIBUTE_LIST *)
              calloc (sizeof (struct SGML_ATTRIBUTE_LIST), 1))
          == (struct SGML_ATTRIBUTE_LIST *) 0
     ) return (struct SGML_ATTRIBUTE_LIST *) 0;

  /*** printf ("sgml_add_attribute.c av=0x%08lX name='%s'\n", av, name); ***/
  if (name != (char *) 0 && *name)
  {
    av->attribute_name= strdup (name);
  }

  /* T2D: analyze attribute value for SGML specific */
  /*      chars and if quoting is necessary         */
  av->attribute_value= cp= strdup (value);
  while (ch= *cp++ & 0x00FF)
  {
    if (ch == '\'') flg |= SAf_value_dquoted;
    else if (ch == '\"') flg |= SAf_value_squoted;
    else if (ch == '\\') flg |= SAf_value_escaped;
    else if (!(  (ch >= 'A' && ch <= 'Z')
              || (ch >= 'a' && ch <= 'z')
              ||  ch == '_' || ch == '-'
              || (ch >= '0' && ch <= '9'))
            ) flg |= SAf_value_dquoted;
  }

  if (flg == 0x00) flg |= SAf_value_noquote;  /* no quote necessary */

  av->flags= SAf_name_malloced | SAf_value_malloced | flg;

  *ot->attr_append= av;
  ot->attr_append= &av->next;

  return av;
}
