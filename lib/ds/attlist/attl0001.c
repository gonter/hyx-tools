/*
 *  FILE %ds/attlist/attl0001.c
 *
 *  manipulation of attribute lists
 *  +  creation of new attribute elements
 *
 *  written:       1994-03-26
 *  latest update: 1997-11-02 12:49:57
 *  $Id: attl0001.c,v 1.3 2002/05/02 06:48:29 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
struct ATTRIBUTE_LIST *al_create_attribute (
char *name,
char *attl,
long type,
void *value)
{
  struct ATTRIBUTE_LIST *al;

  if ((al= (struct ATTRIBUTE_LIST *)
           calloc (sizeof (struct ATTRIBUTE_LIST), 1))
      == (struct ATTRIBUTE_LIST *) 0)
  {
    return (struct ATTRIBUTE_LIST *) 0;
  }

/*** fprintf (stderr, ">>> attrib %s created\n", name); ***/
  al->AL_attl= attl;
  al->AL_name= name;
  al->AL_value= ((al->AL_type= type) == ALty_string_dup)
                ? (void *) strdup ((char *) value)
                : value;

  return al;
}
