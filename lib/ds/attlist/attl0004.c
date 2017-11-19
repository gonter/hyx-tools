/*
 *  FILE %ds/attlist/attl0004.c
 *
 *  manipulation of attribute lists
 *  +  find an attribute element
 *
 *  written:       1994-03-26
 *  latest update: 1997-11-02 12:52:16
 *
 */

#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
struct ATTRIBUTE_LIST *al_find_attribute (
struct ATTRIBUTE_LIST *al,
char *name)
{
  struct ATTRIBUTE_LIST **alp;

  if ((alp= al_getp_attribute (&al, name)) == (struct ATTRIBUTE_LIST **) 0)
    return (struct ATTRIBUTE_LIST *) 0;

  return *alp;
}
