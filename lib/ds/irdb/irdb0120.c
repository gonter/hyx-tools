/*
 *  FILE %ds/irdb/irdb0120.c
 *
 *  irrelational database
 *
 *  written:       1996-04-27
 *  latest update: 1996-04-27 11:00:16
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/strings.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_dbg_post_increment_long (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt,
long value)
{
  long rc;

  rc= irdb_post_increment_long (pos, slots, slot_cnt, value);

  fputs ("post_increment_long '", stdout);
  irdb_dbg_show_slot_names (stdout, slots, slot_cnt);
  printf ("':= value=%ld (rc=%ld)\n", value, rc);

  return rc;
}
