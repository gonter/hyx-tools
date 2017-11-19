/*
 *  FILE %ned/04/ned0434.c
 *
 *  Get path name for the file specified in a window control structure
 *  This works by definition only for files, not for clusters!
 *
 *  written:       1995-10-31
 *  latest update: 1996-09-28 20:41:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

static char path_buffer [MAX_FNM_LENGTH];

/* ------------------------------------------------------------------------ */
char *ned_get_file_path (struct WINDOWCTRL *wc)
{
  struct FILECTRL *fc;
  char *cp;                     /* pointer to file name                     */
  int ii;                       /* position of last path seperator          */

  if (wc == (struct WINDOWCTRL *) 0
      || wc->file_type != 0
      || (fc= (struct FILECTRL *) wc->file_or_frame) == (struct FILECTRL *) 0
      || (cp= fc->FC_fnm_txt) == (char *) 0
     ) return (char *) 0;

  ii= isolate_path (cp);
  strcpy_max (path_buffer, cp, ii+1);

  return path_buffer;
}
