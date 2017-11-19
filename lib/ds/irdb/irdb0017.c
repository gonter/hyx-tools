/*
 *  FILE %ds/irdb/irdb0017.c
 *
 *  irrelational database
 *  same as irdb_locate_info () except that the name of the last
 *  dimension is always a structure which is created, if necessary.
 *
 *  written:       1996-04-08
 *  latest update: 1996-04-26 22:42:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
struct IRDB_HANDLE *irdb_locate_handle (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt,
int create,
long ty)
{
  long *addr;
  struct IRDB_HANDLE *rv= (struct IRDB_HANDLE *) 0;

  if ((addr= irdb_locate_info (pos, slots, slot_cnt, create,
                               (long) IRDBty_struct))
         != (long *) 0
     )
  {
    if ((rv= (struct IRDB_HANDLE *) *addr) == (struct IRDB_HANDLE *) 0
        && create
       )
    {
printf ("[creating handle for %s, type=%ld]\n", slots [slot_cnt-1], ty);
      rv= irdb_new_struct_handle ((char *) 0, ty);
      *addr= (long) rv;
    }
  }

  return rv;
}
