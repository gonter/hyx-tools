/*
 *  FILE %ds/irdb/irdb0012.c
 *
 *  irrelational database
 *
 *  written:       1996-04-06
 *  latest update: 1996-04-14 20:28:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_store_to_struct (
struct IRDB_HANDLE *hnd,
char *slot,
long value)
{
  int rc= 0;

  if (hnd == (struct IRDB_HANDLE *) 0
      || hnd->IRDB_type != IRDBty_struct
     )
    return -1;

  ytree_set_value ((struct YTREE **) &hnd->IRDB_payload,
                   (unsigned char *) slot,
                   value);

  return rc;
}
