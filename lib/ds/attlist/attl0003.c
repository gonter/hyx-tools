/*
 *  FILE %ds/attlist/attl0003.c
 *
 *  manipulation of attribute lists
 *  +  set an attribute value
 *
 *  written:       1994-03-26
 *  latest update: 1997-11-02 12:51:45
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
struct ATTRIBUTE_LIST *al_set_attribute (
struct ATTRIBUTE_LIST **alp,
char *name,
char *attl,
long type,
void *value)
{
  struct ATTRIBUTE_LIST *al;

  if (alp == (struct ATTRIBUTE_LIST **) 0) return (struct ATTRIBUTE_LIST *) 0;

  alp= al_getp_attribute (alp, name);
  al= *alp;

  if (al == (struct ATTRIBUTE_LIST *) 0)
  {
    *alp= al= al_create_attribute (name, attl, type, value);
  }
  else
  {
    if (al->AL_value != (void *) 0
        && al->AL_type == ALty_string_dup) free ((char *) al->AL_value);

    al->AL_value= ((al->AL_type= type) == ALty_string_dup)
                  ? (void *) strdup (value)
                  : value;
  }

  return al;
}
