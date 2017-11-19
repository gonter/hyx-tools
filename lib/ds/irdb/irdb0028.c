/*
 *  FILE %ds/irdb/irdb0028.c
 *
 *  irrelational database
 *
 *  written:       1996-05-06
 *  latest update: 1996-05-06  0:57:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/irdb.h>

#ifdef DEBUG2
#include <stdio.h>
#endif /* DEBUG2 */

/* ------------------------------------------------------------------------ */
long irdb_get_increment_long (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt)
{
  long *info;

  if ((info= irdb_locate_info (pos, slots, slot_cnt, 1, (long) IRDBty_int))
      == (long *) 0
     )
    return 0L;

#ifdef DEBUG2
printf ("irdb0019: setting value\n");
#endif /* DEBUG2 */

  return *info;
}
