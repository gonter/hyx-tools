/*
 *  FILE %ned/08/ned0858b.c
 *
 *  see also:
 *  - ned_rename_frame ()
 *
 *  written:       1996-07-28
 *  latest update: 1999-04-25 16:33:39
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

extern char *ned_renamed_object;

/* ------------------------------------------------------------------------ */
int ned_cb_rename_frame (char *str, int size, int malloced, void *cb_data)
{
  struct WINDOWCTRL *wc;

#ifdef MSDOS
  size;
#endif /* MSDOS */

  if ((wc= (struct WINDOWCTRL *) cb_data) != (struct WINDOWCTRL *) 0
      && str != (char *) 0
     )
  {
    ned_rename_frame (wc, str, wc->file_format);

    if (ned_renamed_object != (char *) 0
        && str != ned_renamed_object    /* str *can* point to that buffer   */
       )                                /* since this is a callback fnc.    */
      strcpy_max (ned_renamed_object, str, MAX_FNM_LENGTH);

    ned_wc_memorize_location (wc);
    ned_display_window (wc);
    if (malloced) free (str);
  }

  return 0;
}
