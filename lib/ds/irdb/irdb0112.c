/*
 *  FILE %ds/irdb/irdb0112.c
 *
 *  irrelational database
 *
 *  written:       1996-04-06
 *  latest update: 1996-04-06 12:53:45
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/strings.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_dbg_store_to_struct (
struct IRDB_HANDLE *hnd,
char *slot,
long value)
{
  int rc;

  rc= irdb_store_to_struct (hnd, slot, value);

  printf ("store to struct '%s': slot='%s' value='%s' rc=%d\n",
#ifdef IRDB_USE_CLASS_NAME
          XSTR (hnd->IRDB_class_name),
#else
          "anon",
#endif /* !IRDB_USE_CLASS_NAME */
          slot, value, rc);

  return rc;
}
