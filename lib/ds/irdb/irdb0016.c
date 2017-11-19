/*
 *  FILE %ds/irdb/irdb0016.c
 *
 *  irrelational database
 *
 *  written:       1996-04-06
 *  latest update: 1996-08-08 17:35:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdio.h>
#include <gg/strings.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_replace_string (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt,
char *value)
{
  int rc= 0;
  long *info;
  char *str;

  if ((info= irdb_locate_info (pos, slots, slot_cnt, 1, (long) IRDBty_string))
      == (long *) 0
     )
    return -1;

  str= (char *) *info;
  free_or_what (str);

  str= strdup (value);
  *info= (long) str;

  return rc;
}
