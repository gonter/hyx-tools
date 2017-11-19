/*
 *  File %sbr/makepath.c
 *
 *  verify that the given directory path exists and create
 *  missing directories
 *
 *  written:       1991 11 08
 *  latest update: 1997-03-23 14:57:51
 *
 */

#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#ifdef MSDOS
#include <direct.h>
/* AIX has the mkdir() prototype in sys/stat.h */
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <gg/filename.h>

extern int errno;

/* ------------------------------------------------------------------------ */
int make_path (
char *path,             /* complete path to generate            */
int flags)              /* bit 0: last part is a file name      */
{
  struct stat st;
  int i, c;
  int rc;

#ifdef DEBUG
  printf (">> make_path (%s)\n", %s);
#endif /* DEBUG */

  for (i= 0;; i++)
  {
    c= path[i];
    if (c == 0 && (flags & 0x0001)) break;
    if (c == '/' || c == '\\' || c == 0)
    {
      path[i]= 0;
      rc= stat (path, &st);

#ifdef DEBUG
printf (">> stat (%s) -> rc=%d errno=%d\n", path, rc, errno);
#endif /* DEBUG */

      if (rc == 0)
      {
        path[i]= (char) c;
        if (!(st.st_mode & S_IFDIR)) return -1;
      }
      else
      {
        if (errno == ENOENT)
#ifdef MSDOS
          mkdir (path);
#else
          mkdir (path, 0755);   /* T2D: umask or something? */
#endif

        path[i]= (char) c;
      }
    }
    if (c == 0) break;
  }

  return 0;
}
