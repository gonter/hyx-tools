/*
 *  FILE %ds/irdb/irdb0020.c
 *
 *  irrelational database
 *
 *  written:       1996-04-08
 *  latest update: 1996-04-26 22:43:14
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
long irdb_pre_increment_long (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt,
long value)
{
  long *info;

  if ((info= irdb_locate_info (pos, slots, slot_cnt, 1, (long) IRDBty_int))
      == (long *) 0
     )
    return 0L;

#ifdef DEBUG2
printf ("irdb0020: >>> setting value\n");
#endif /* DEBUG2 */

  *info += value;

  return *info;
}
