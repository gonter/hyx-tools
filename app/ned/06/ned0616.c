/*
 *  FILE %ned/06/ned0616.c
 *
 *  assign a name to a window, either for the first time or rename it.
 *
 *  written:       1987 04 08
 *                 1990 04 01: function of p_fnm (renaming of a unnamed
 *                             window) rolled in.  Thus, the function p_fnm
 *                             itself became obsolete and was removed.  See
 *                             also changes in the editor tables ned0001?.c.
 *                 1991 02 03: revision
 *                 1994-06-19: ned_rename_file () isolated from this module
 *  latest update: 1999-04-25 16:32:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern char *ned_renamed_object;
extern char *default_help_cluster;
extern char *default_help_rename_frame;

/* ------------------------------------------------------------------------ */
int ned_rename_object ()        /* ^K N: rename file or frame               */
{
  int rc= 0;
  struct FRAMECTRL *fc;

  if (ned_renamed_object == (char *) 0)
  {
    if ((ned_renamed_object= malloc (MAX_FNM_LENGTH)) == (char *) 0)
      return -1;

    ned_renamed_object [0]= 0;
  }

  switch (aw->file_type)
  {
    case FTY_HYPER:
      fc= (struct FRAMECTRL *) aw->file_or_frame;
      strcpy_max (ned_renamed_object, fc->frame_name, MAX_FNM_LENGTH);

      ned_prompt_string ("New Frame Name:", ned_renamed_object,
                         MAX_FNM_LENGTH,
                         default_help_cluster,
                         default_help_rename_frame,
                         ned_cb_rename_frame, (void *) aw);

      break;

    case FTY_PLAIN:
      rc= ned_rename_file (ned_renamed_object, MAX_FNM_LENGTH);
      break;
    /* case FTY_FTRWDW: don't rename ... */
  }

  return rc;
}
