/*
 *  FILE %sbr/fnmovwr.c
 *
 *  do not overwerite files
 *
 *  written:       1997-09-14
 *  latest update: 1997-09-14 16:15:20
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>

static int initialized= 0;

/* ------------------------------------------------------------------------ */
char *alternative_filename (char *fnm, int extra)
{
  struct stat st;
  char *new_name;               /* newly generated filename                 */
  char *file_part;              /* filename part of a full path             */
  char *extension_part;         /* extension part of original filename      */
  char *new_pattern;            /* format for new filename                  */
  int tries;
  int num;

  if (fnm == (char *) 0 || *fnm == 0
      || stat (fnm, &st) != 0
     ) return (char *) 0;

  /* file already exists; find a new name */
  new_name= strdup_extra (fnm, extra+9);
  file_part= get_filename_from_path (new_name);
  extension_part= tell_extension (fnm);

  new_pattern= (*extension_part == 0) ? "qq%06d" : "qq%06d.%s";

  if (!initialized)
  {
    srand ((int) time ((time_t *) 0));
    initialized= 1;
  }

  for (tries= 10000; tries-- > 0;)
  {
    num= rand ();
    sprintf (file_part, new_pattern, num, extension_part);
    if (stat (new_name, &st) != 0) break;
  }

  return new_name;
}
