/*
 *  FILE %ds/irdb/irdb0116.c
 *
 *  irrelational database
 *
 *  written:       1996-04-06
 *  latest update: 1996-04-26 22:44:42
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/strings.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_dbg_replace_string (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt,
char *value)
{
  int rc;

  rc= irdb_replace_string (pos, slots, slot_cnt, value);

  fputs ("replace string '", stdout);
  irdb_dbg_show_slot_names (stdout, slots, slot_cnt);
  printf ("': value='%s' rc=%d\n", value, rc);

  return rc;
}
