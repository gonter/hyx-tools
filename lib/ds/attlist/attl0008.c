/*
 *  FILE %ds/attlist/attl0008.c
 *
 *  manipulation of attribute lists
 *  +  creation of new attribute elements
 *
 *  written:       2002-04-20
 *  latest update: 2002-04-20 18:37:36
 *  $Id: attl0008.c,v 1.1 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
int al_add_attribute (
ATTLIST *al,
char *name,
char *attl,
long type,
void *value)
{
  struct ATTRIBUTE_LIST *al2;

  if (al == (ATTLIST *) 0
      || (al2= al_create_attribute (name, attl, type, value))
         == (struct ATTRIBUTE_LIST *) 0
     )
  {
    return -1;
  }

  *(al->AL_append)= al2;
  al->AL_append= &al2->AL_next;

  return 0;
}
