/*
 *  FILE %ds/rdtp/rdtp0346.c
 *
 *  restructured dynamic text parser
 *  transform a tag structure to a string
 *
 *  written:       1997-06-16
 *  latest update: 1997-11-26 12:52:40
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
char *sgml_tag_to_string (
struct SGML_OPENING_TAG *ot,
char *buffer,
int max_size,
int extra)
{
  struct SGML_ATTRIBUTE_LIST *av;
  struct SGML_TAG_NAME *tn;
  char *name;
  char *dest;
  char *cp;
  int quote= 0; /* 0 or quote character to be used */
  int size= 0;

  if (ot == (struct SGML_OPENING_TAG *) 0
      || (tn= ot->tag_name) == (struct SGML_TAG_NAME *) 0
      || (name= tn->tag_name) == (char *) 0
     )
  {
    return (char *) 0;
  }

  if (buffer == (char *) 0)
  {
    if ((size= sgml_space_required (ot)) > 0
        && (max_size= size+5+extra) > 0
        && (buffer= malloc (max_size)) == (char *) 0
       ) return (char *) 0;

    max_size--;
  }

  dest= buffer;
  *dest++= '<';
  max_size -= 2;       /* reserve space for '>' */
  size= strcpy2_max (dest, name, max_size);
  max_size -= size;
  dest += size;

  for (av= ot->attributes;
       av != (struct SGML_ATTRIBUTE_LIST *) 0;
       av= av->next
      )
  {
    if (max_size < 2) break;

    *dest++= ' ';
    max_size--;
    quote= (av->attribute_type == SAt_NED)
           ? 0 : '\"';

    if (quote)
    switch (av->flags & SAf_value_quote_mask)
    {
      case SAf_value_noquote: quote= 0; break;
      case SAf_value_squoted: quote= '\''; break;
      default: quote= '\"'; break;
    }

    if ((cp= av->attribute_name) != (char *) 0)
    {
      size= strcpy2_max (dest, cp, max_size);
      dest += size;
      *dest++= '=';
      max_size -= size+1;
    }

    if (max_size < 3) break;
    if ((cp= av->attribute_value) != (char *) 0)
    {
      if (quote) *dest++= (char) quote;
      max_size -= 2;
      size= strcpy2_max (dest, cp, max_size);
      dest += size;
      max_size -= size;
      if (quote) *dest++= (char) quote;
    }
  }

  *dest++= '>';
  *dest= 0;

  return buffer;
}
