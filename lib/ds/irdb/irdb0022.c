/*
 *  FILE %ds/irdb/irdb0022.c
 *
 *  irrelational database
 *  - load an irdb handle from the file at current position
 *
 *  written:       1996-04-27
 *  latest update: 1996-05-05 12:01:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
struct IRDB_HANDLE *irdb_load_handle (FILE *fi)
{
  struct IRDB_HANDLE *hnd= (struct IRDB_HANDLE *) 0;
#ifdef IRDB_USE_CLASS_NAME
#define BSIZ 128
  char buffer [BSIZ];
#endif /* IRDB_USE_CLASS_NAME */

  if (fi != (FILE *) 0
      && (hnd= calloc (sizeof (struct IRDB_HANDLE), 1))
         != (struct IRDB_HANDLE *) 0
     )
  {
printf ("irdb0022: restoring handle\n");
    hnd->IRDB_type=         dpp_fread_long (fi, 4);
    hnd->IRDB_payload_size= dpp_fread_long (fi, 4);
    hnd->IRDB_payload=      dpp_fread_long (fi, 4);
    hnd->IRDB_payload_type= dpp_fread_long (fi, 4);

#ifdef IRDB_USE_CLASS_NAME
    hnd->IRDB_class_name= irdb_load_string (fi, buffer, BSIZ);
#endif /* IRDB_USE_CLASS_NAME */
  }

  return hnd;
}
