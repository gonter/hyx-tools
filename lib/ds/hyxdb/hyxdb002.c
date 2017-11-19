/*
 *  FILE %ds/hyxdb/hyxdb002.c
 *
 *  hyxdb: HYX Database Management
 *  create a new object
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
#include <string.h>
#include <gg/hyxdb.h>

/* ------------------------------------------------------------------------ */
struct HYXDB_OBJECT *hyxdb_new_object (
struct HYXDB_CONTROL *ctrl,
char *frame_name,
long id)
{
  struct HYXDB_OBJECT *obj;

  if ((obj= (struct HYXDB_OBJECT *) calloc (sizeof (struct HYXDB_OBJECT), 1))
            == (struct HYXDB_OBJECT *) 0)
    return (struct HYXDB_OBJECT *) 0;

  if (frame_name != (char *) 0) obj->frame_name= strdup (frame_name);
  obj->OID= id;
  obj->element_destructor= ctrl->element_destructor;

  return obj;
}

