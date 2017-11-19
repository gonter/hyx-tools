/*
 *  FILE %ds/irdb/irdb0009.c
 *
 *  irrelational database
 *
 *  written:       1996-04-27
 *  latest update: 1996-04-28 12:16:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
struct IRDB_POS *irdb_new_pos (char *fnm, char *cln, int is_new)
{
  struct IRDB_HANDLE *handle;
  struct IRDB_POS *pos;
  FILE *f;

  if ((pos= calloc (sizeof (struct IRDB_POS), 1)) == (struct IRDB_POS *) 0)
  {
    return (struct IRDB_POS *) 0;
  }

  if (is_new)
  {
    if ((f= fopen (fnm, "wb")) == (FILE *) 0)
    {
ERROR:
      free (pos);
      return (struct IRDB_POS *) 0;
    }

    if ((handle= irdb_new_struct_handle (cln, (long) IRDBty_struct))
         == (struct IRDB_HANDLE *) 0)
      goto ERROR;
  }
  else
  {
    if ((f= fopen (fnm, "wb")) == (FILE *) 0) goto ERROR;
    handle= irdb_load_handle (f);
  }
  fclose (f);

  pos->IRDB_handle= handle;
  pos->IRDB_file_name= strdup (fnm);
  pos->IRDB_open_mode= IRDBom_closed;
  pos->IRDB_is_new= is_new;

  return pos;
}
