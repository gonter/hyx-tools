/*
 *  FILE 1996-04-06
 *
 *  irrelational database
 *
 *  written:       1996-04-06
 *  latest update: 1996-04-26 22:41:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_exists (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt)
{
  long *loc;

  loc= irdb_locate_info (pos, slots, slot_cnt, 0, 0L);

  return (loc == (long *) 0) ? 0 : 1;
}
