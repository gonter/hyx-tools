/*
 *  FILE %ds/irdb/irdb0008.c
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
long irdb_core_form (long type)
{
  switch ((int) type)
  {
    case IRDBty_string_dumped:         return IRDBty_string;
    case IRDBty_block_dumped:          return IRDBty_block;
    case IRDBty_array_dumped:          return IRDBty_array;
    case IRDBty_struct_dumped:         return IRDBty_struct;
  }

  return type;
}
