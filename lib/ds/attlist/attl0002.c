/*
 *  FILE %ds/attlist/attl0002.c
 *
 *  manipulation of attribute lists
 *  +  get a pointer to a pointer to an attribute element
 *
 *  written:       1994-03-26
 *  latest update: 1997-11-02 12:51:13
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
struct ATTRIBUTE_LIST **al_getp_attribute (
struct ATTRIBUTE_LIST **alp,
char *name)
{
  struct ATTRIBUTE_LIST *al;

  for (; (al= *alp) != (struct ATTRIBUTE_LIST *) 0; alp= &al->AL_next)
  {
    if (strcmp (al->AL_name, name) == 0)
    {
fprintf (stderr, ">>> attrib %s found\n", name);
      return alp;
    }
  }

  return alp;
}
