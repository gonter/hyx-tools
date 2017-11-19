/*
 *  FILE %ned/06/ned0630.c
 *
 *  File- und Windowoperationen:
 *    setup the file name in the FILECTRL structure
 *
 *  written:       1994-08-12
 *  latest update: 1999-04-25 16:32:25
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
char *FC_setup_filenames (
struct FILECTRL *fc,
char *specified,
char *ftr_name)
{
  char *real_fnm, *virtual_fnm, *short_title;

  if (fc == (struct FILECTRL *) 0
      || filename_definition (specified, &real_fnm, &virtual_fnm, (char *) 0)
         != 0
     )
    return (char *) 0;

  fc->FC_fnm_txt= real_fnm;
  fc->FC_fnm_ftr= (ftr_name == (char *) 0)
                  ? fnmcpy2 (real_fnm, ".ftr")
                  : strdup (ftr_name);
  fc->FC_fnm_bak= fnmcpy2 (real_fnm, ".bak");

  if (virtual_fnm == (char *) 0)
  {
    virtual_fnm= strdup (specified);
    short_title= (char *) 0;
  }
  else short_title= virtual_fnm;

  return short_title;
}
