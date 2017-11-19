/*
 *  FILE %ds/irdb/irdb0019.c
 *
 *  irrelational database
 *
 *  written:       1996-04-08
 *  latest update: 1996-04-26 22:43:36
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
long irdb_post_increment_long (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt,
long value)
{
  long rc= 0;
  long *info;

  if ((info= irdb_locate_info (pos, slots, slot_cnt, 1, (long) IRDBty_int))
      == (long *) 0
     )
    return 0L;

#ifdef DEBUG2
printf ("irdb0019: setting value\n");
#endif /* DEBUG2 */

  rc= *info;
  *info += value;

  return rc;
}
