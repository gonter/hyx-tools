/*
 *  FILE %ds/irdb/irdb0007.c
 *
 *  irrelational database
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-14 19:55:02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_dumped_form (long type)
{
  switch ((int) type)
  {
    case IRDBty_string:         return IRDBty_string_dumped;
    case IRDBty_block:          return IRDBty_block_dumped;
    case IRDBty_array:          return IRDBty_array_dumped;
    case IRDBty_struct:         return IRDBty_struct_dumped;
  }

  return type;
}
