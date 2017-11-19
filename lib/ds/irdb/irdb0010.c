/*
 *  FILE %ds/irdb/irdb0010.c
 *
 *  irrelational database
 *
 *  written:       1996-04-05
 *  latest update: 1996-04-27 14:12:10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
struct IRDB_HANDLE *irdb_new_handle (long ty, char *cln)
{
  struct IRDB_HANDLE *handle;

  if ((handle= calloc (sizeof (struct IRDB_HANDLE), 1))
      != (struct IRDB_HANDLE *) 0)
  {
    handle->IRDB_type= ty;
#ifdef IRDB_USE_CLASS_NAME
    if (cln != (char *) 0 && *cln != 0)
      handle->IRDB_class_name= strdup (cln);
#else
#ifdef MSDOS
    cln;
#endif /* MSDOS */
#endif /* !IRDB_USE_CLASS_NAME */
  }

  return handle;
}
