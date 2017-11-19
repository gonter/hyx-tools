/*
 *  FILE %ds/hyxdb/hyxdb003.c
 *
 *  hyxdb: HYX Database Management
 *  insert a (new) attribute to a given object
 *  return number of values for the attribute
 *
 *  written:       1997-11-09
 *  latest update: 1997-11-09 11:22:17
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/hyxdb.h>

/* ------------------------------------------------------------------------ */
long hyxdb_insert_attribute (
struct HYXDB_OBJECT *obj,
char *attr_name,
struct HYXDB_VALUE *attr_value,
int insert_mode)
{
  struct YTREE *yt;
  struct ARRAY_CONTROL *values;

  if (obj == (struct HYXDB_OBJECT *) 0 || attr_name == (char *) 0)
    return -1L;

  /* locate attribute value list for the given attribute name */
  yt= ytree_insert_word (&obj->attr, (unsigned char *) attr_name);

  if (yt->YT_flags & YTflag_EOW)
  { /* attribute has already been defined */
    values= (struct ARRAY_CONTROL *) yt->YT_info;
    if (insert_mode == HYXDB_replace) { array_dispose (values); goto NEW; }
  }
  else
  { /* attribute is new */
    if (insert_mode == HYXDB_update)
    { /* there should already be some values under this attribute ! */
      return -1L;
    }

NEW:
    values= array_new ();
    values->element_destructor= obj->element_destructor;
    yt->YT_info= (long) values;
    yt->YT_flags |= YTflag_EOW;
  }

  array_push (values, (void *) attr_value);

  return array_elements (values);
}
