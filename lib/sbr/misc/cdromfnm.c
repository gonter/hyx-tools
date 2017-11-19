/*
 *  FILE %sbr/cdromfnm.c
 *
 *  change a filename into a format that is also good for CD Roms
 *
 *  written:       1996-08-11
 *  latest update: 1996-08-11 17:23:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
int cdrom_file_name (char *fnm)
{
  int ch;

  if (fnm == (char *) 0) return -1;

  while ((ch= *fnm & 0x0FF) != 0)
  {
    if (ch >= 'A' && ch <= 'Z') ch= ch - 'A' + 'a'; else
    if (!((ch >= '0' && ch <= '9')
          || (ch >= 'a' && ch <= 'z')
          || ch == '@' || ch == '-' || ch == '.'
         )
       )
      ch= '_';

    *fnm++= (char) ch;
  }

  return 0;
}
