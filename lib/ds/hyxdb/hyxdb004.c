/*
 *  FILE %ds/hyxdb/hyxdb004.c
 *
 *  hyxdb: HYX Database Management
 *  retrieve the values for an attribute in an object
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
struct ARRAY_CONTROL *hyxdb_get_attribute_values (
struct HYXDB_OBJECT *obj,
char *attr_name)
{
  struct ARRAY_CONTROL *values= (struct ARRAY_CONTROL *) 0;

  if (obj != (struct HYXDB_OBJECT *) 0
      && attr_name != (char *) 0)
  {
    values= (struct ARRAY_CONTROL *)
            ytree_get_value (obj->attr, (unsigned char *) attr_name);
  }

  return values;
}
