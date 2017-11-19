/*
 *  FILE %ds/hyxdb/hyxdb007.c
 *
 *  hyxdb: new value
 *
 *  written:       1997-11-09
 *  latest update: 1997-11-09 13:01:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/sbr.h>
#include <gg/hyxdb.h>

/* ------------------------------------------------------------------------ */
struct HYXDB_VALUE *hyxdb_new_value (
int format,
void *value,
long size)
{
  struct HYXDB_VALUE *val;

  if ((val= (struct HYXDB_VALUE *) calloc (sizeof (struct HYXDB_VALUE), 1))
            == (struct HYXDB_VALUE *) 0
     )
   return (struct HYXDB_VALUE *) 0;

  val->format= format;
  val->size=   size;
  val->value=  value;

  return val;
}
