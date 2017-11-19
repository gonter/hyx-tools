/*
 *  FILE %sbr/fnmreal.c
 *
 *  Find absolute filename of a specified file file relative
 *  to a specified assumed path or the current working directory.
 *
 *  Resolves references to the current (./) and the parrent (../)
 *  working directory.
 *
 *  written:       1994-08-12
 *  latest update: 1996-03-17 16:17:27
 *  $Id: fnmreal.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/filename.h>

#ifdef DEBUG
#include <stdio.h>
#define DFILE stdout
#endif

/* ------------------------------------------------------------------------ */
char *real_filename (const char *spec, char *assumed_path)
{
  int ch;                       /* examined character in specified path     */
  int ch2;                      /* next character ...                       */
  char *cpath;                  /* buffer for correct path, large enough..  */
  char *cp;                     /* pointer into current path                */
  int cpath_offset= 0;          /* index into corrected path                */
  int spec_offset= 0;           /* index into examined specified path       */
  int cycle= 0;

  if (spec == (char *) 0
      || (cpath= duplicate_assumed_path (assumed_path)) == (char *) 0
     ) return (char *) 0;

  /* NOTE: *spec == 0 is allowed as a refrence to the current directory.    */
  /* NOTE: cpath is allocated suitably large to hold a valid filename.      */

  cpath_offset= strlen (cpath);
#ifdef DEBUG
  fprintf (DFILE, "cpath='%s' cpath_offset=%d\n", cpath, cpath_offset);
#endif /* DEBUG */

DOITAGAIN:
    cycle++;
    ch= spec [spec_offset];
    ch2= spec [spec_offset+1];
#ifdef DEBUG3
    fprintf (DFILE, "cycle=%d spec_offset=%d ch=%c ch2=%c\n",
            cycle, spec_offset, ch, ch2);
#endif /* DEBUG */

    switch (ch)
    {
      case 0:
#ifdef DEBUG4
        fprintf (DFILE, "ch==0: cpath_offset=%d spec_offset=%d\n",
                cpath_offset, spec_offset);
#endif /* DEBUG */
        break;

      case '/':
#ifdef MSDOS
      case '\\':
        if (cycle == 1)
        {
          cpath_offset= 2;      /* in DOS there's also a drive letter       */
          cpath [cpath_offset]= 0;
        }
#else
        if (cycle == 1)
        {
          cpath_offset= 0;
          cpath [cpath_offset]= 0;
        }
#endif /* !MSDOS */
        break;

      case '.':
        if (ch2 == 0)
        {
          spec_offset++;
          break;
        }

        if (ch2 == '.')
        {
          if ((cp= strridx (cpath, '/')) != (char *) 0
#ifdef MSDOS
              || (cp= strridx (cpath, '\\')) != (char *) 0
#endif /* MSDOS */
             ) *cp= 0;

          spec_offset += 2;
          if (spec [spec_offset] != 0) spec_offset++;
          goto DOITAGAIN;
        }

        if (ch2 == '/'
#ifdef MSDOS
            || ch2 == '\\'
#endif /* MSDOS */
           )
        {
          spec_offset += 2;
          goto DOITAGAIN;
        }

        /* otherwise it must be a filename (not in DOS, however) */

      default:
#ifdef MSDOS
         /* path name contains drive letter?? */
        if (cycle == 1 && ch != 0 && ch2 == ':')
        {
#ifdef DEBUG
          fprintf (DFILE, "drive letter: '%c%c'\n", ch, ch2);
#endif /* DEBUG */
          if (ch >= 'A' && ch <= 'Z') ch= ch - 'A' + 'a';
          cpath [0]= (char) ch;
          cpath [1]= ':';
          spec_offset += 2;
          ch2= spec [spec_offset];
          if (ch2 == '/' || ch2 == '\\')
          {
            cpath_offset= 3;
            spec_offset++;
            cpath [cpath_offset]= 0;
#ifdef DEBUG
            fprintf (DFILE, "cpath= '%s'\n", cpath);
#endif /* DEBUG */
            goto DOITAGAIN;
          }

          cpath [2]= '\\';
          getpwd (cpath+3, ch-'a'+1);
#ifdef DEBUG
          fprintf (DFILE, "cpath= '%s'\n", cpath);
#endif /* DEBUG */
          goto DOITAGAIN;
        }
#endif /* MSDOS */

        cpath_offset= strlen (cpath);
#ifdef DEBUG5
        fprintf (DFILE, "[fnmreal] fixing: cpath='%s' cpath_offset=%d\n",
                cpath, cpath_offset);
#endif /* DEBUG */

#ifdef MSDOS
        if ((ch= cpath [cpath_offset-1]) != '/' && ch != '\\')
          cpath [cpath_offset++]= '\\';
#else /* MSDOS */
        if (cpath [cpath_offset-1] != '/')
          cpath [cpath_offset++]= '/';
#endif /* !MSDOS */
        cpath [cpath_offset]= 0;

        break;
    }

  cpath_offset= strlen (cpath);
  /* must be done, otherwise ned crashes under MSDOS... why on earth??? */
  strcpy (cpath+cpath_offset, spec+spec_offset);

#ifdef MSDOS
  if ((cpath_offset= strlen (cpath)) == 2)
  {
    cpath [2]= '\\';
    cpath [3]= 0;
  }
#endif /* MSDOS */

#ifdef DEBUG
  fprintf (DFILE, "[fnmreal] END: cpath='%s'\n", cpath);
#endif /* DEBUG */

  return cpath;
}
