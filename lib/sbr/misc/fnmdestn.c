/*
 *  FILE %sbr/fnmdestn.c
 *
 *  return the name of a transfer filename
 *
 *  written:       1996-07-14
 *  latest update: 1999-04-25 17:00:21
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *get_destination_name (
char *dest_dir,         /* destination directory                            */
char *from,             /* old filename                                     */
char *result,           /* result buffer; malloced if NULL                  */
int mk_path,            /* 1 ... verify existence of path                   */
int rotfnm)             /* 1 ... rotate file name                           */
{
  char *malloced= (char *) 0;
  char *fnm;
  int dest_size;
  int ch;

  if (dest_dir == (char *) 0
      || from == (char *) 0
      || (dest_size= strlen (dest_dir)) == 0
     )
    return (char *) 0;

  /* prepare result; alloc buffer if not already passed as argument */
  if (result == (char *) 0
      && (result= malloced= malloc (dest_size +strlen (from)+2)) == (char *) 0
     )
    return (char *) 0;

  /* append dest_dir, a slash and the given filename */
  strcpy (result, dest_dir);
  dest_size--;

  if ((ch= result [dest_size]) != '/'
#ifdef MSDOS
      && ch != '\\'
#endif /* MSDOS */
     )
  { /* dest_dir does not end with a slash */
    dest_size++;
    result [dest_size++]= '/';
  }

  strcpy (result+dest_size, from);

  if (rotfnm)
  {
    if ((fnm= get_filename_from_path (result)) == (char *) 0)
    {
ERROR:
      free_or_what (malloced);
      return (char *) 0;
    }
    rotate13 (fnm);
  }

  if (mk_path && make_path (result, 0x0001) != 0) goto ERROR;

  return result;
}
