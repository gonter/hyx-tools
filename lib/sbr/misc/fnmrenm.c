/*
 *  FILE %sbr/fnmrenm.c
 *
 *  rename a file
 *
 *  T2D: add code to overwrite the original file too
 *
 *  written:       1996-07-14
 *  latest update: 1997-05-30 12:58:14
 *
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
int filename_rename (
char *from,             /* old filename                                     */
char *to,               /* new filename                                     */
int mode)               /* rename mode:                                     */
                        /* 0 ... don't rename (silly)                       */
                        /* 1 ... just rename the file                       */
                        /* 2 ... rename the file to a rot13 version         */
                        /* 3 ... like 2 but don't delete dest. filename     */
{
  char *rotnm;
  char *fnm;

  switch (mode)
  {
    default:
      break;

    case 1:
NOROT:
      unlink (to);
      rename (from, to);
      break;

    case 2:
    case 3:
      if ((rotnm= strdup_extra (to, 2)) == (char *) 0
          || (fnm= get_filename_from_path (rotnm)) == (char *) 0
         ) goto NOROT;

      rotate13 (fnm);
      /** printf (">> rename '%s' to '%s'; fnm='%s'\n", from, rotnm, fnm); **/

      if (mode == 2) unlink (to);
      rename (from, rotnm);
      free (rotnm);
      break;
  }

  return 0;
}
