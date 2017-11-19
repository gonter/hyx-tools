/*
 *  FILE %ds/irdb/irdb0024.c
 *
 *  irrelational database
 *
 *  written:       1996-04-28
 *  latest update: 1996-04-28 12:01:51
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
FILE *irdb_get_pos_file_pointer (
struct IRDB_POS *pos,
int open_mode)
{
  FILE *fp= (FILE *) 0;
  int current_mode;

  if (pos != (struct IRDB_POS *) 0)
  {
    if ((current_mode= pos->IRDB_open_mode) == open_mode)
      return pos->IRDB_file;

    if (current_mode == IRDBom_read
        || current_mode == IRDBom_write
        || current_mode == IRDBom_overwrite
       )
      fclose (pos->IRDB_file);

    pos->IRDB_file= (FILE *) 0;
    pos->IRDB_open_mode= IRDBom_closed;

    switch (open_mode)
    {
      case IRDBom_read:
        fp= fopen (pos->IRDB_file_name, "rb");
        break;
      case IRDBom_write:
        fp= fopen (pos->IRDB_file_name, "wb");
        break;
      case IRDBom_overwrite:
        fp= fopen (pos->IRDB_file_name, "r+b");
        break;
    }

    if (fp != (FILE *) 0)
    {
      pos->IRDB_file= fp;
      pos->IRDB_open_mode= open_mode;
    }
  }

  return fp;
}
