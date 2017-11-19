/*
 *  FILE %ds/irdb/irdb0011.c
 *
 *  irrelational database
 *
 *  written:       1996-04-06
 *  latest update: 1996-04-06  8:27:12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
struct IRDB_HANDLE *irdb_new_struct_handle (char *cln, long payload_type)
{
  struct IRDB_HANDLE *handle;

  if ((handle= irdb_new_handle ((long) IRDBty_struct, cln))
      != (struct IRDB_HANDLE *) 0)
  {
    handle->IRDB_payload_type= payload_type;
  }

  return handle;
}
