/*
 *  FILE %ds/irdb/irdb0106.c
 *
 *  irrelational database
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-14 19:03:47
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
char *irdb_type (long type)
{
  switch ((int) type)
  {
    case IRDBty_int:            return "int";
    case IRDBty_float:          return "float";
    case IRDBty_string:         return "string";
    case IRDBty_block:          return "block";
    case IRDBty_array:          return "array";
    case IRDBty_struct:         return "struct";
    case IRDBty_struct_dumped:  return "struct_dumped";
    case IRDBty_string_dumped:  return "string_dumped";
    case IRDBty_array_dumped:   return "array_dumped";
  }

  return "(unknown)";
}
