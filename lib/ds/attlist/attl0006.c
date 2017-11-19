/*
 *  FILE %ds/attlist/attl0006.c
 *
 *  manipulation of attribute lists
 *  +  find an attribute element
 *
 *  written:       1994-10-30
 *  latest update: 1997-11-02 12:54:50
 *  $Id: attl0006.c,v 1.2 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
void *al_find_attribute_value (
struct ATTRIBUTE_LIST *al,
char *name)
{
  struct ATTRIBUTE_LIST **alp;

  if ((alp= al_getp_attribute (&al, name)) == (struct ATTRIBUTE_LIST **) 0
      || (al= *alp) == (struct ATTRIBUTE_LIST *) 0
     )
    return (void *) 0;

  return al->AL_value;
}
