/*
 *  FILE %ds/irdb/irdb0107.c
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
long irdb_dbg_show_slot_names (
FILE *fo,
char *slots[],
int slot_cnt)
{
  int i= 0;

  for (; slot_cnt > 1; slot_cnt--)
  {
    fputs (slots [i++], fo);
    fputc ('.', fo);
  }

  if (slot_cnt > 0) fputs (slots [i++], fo);

  return 0;
}
