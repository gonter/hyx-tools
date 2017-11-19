/*
 *  FILE %ned/06/ned0610c.c
 *
 *  open a window for a give filename
 *
 *  written:       1995-11-26: isolated from ned0610.c
 *  latest update: 2000-08-11  6:32:06
 *  $Id: ned0610c.c,v 1.6 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern char *default_help_cluster;
extern char *default_help_open_file;

/* ------------------------------------------------------------------------ */
int ned_open_file (
const char *fnm,
const char *help_cluster,
const char *help_frame,
int flags)              /* NED_OPENF_*                                      */
{
  if (help_cluster == (char *) 0) help_cluster= default_help_cluster;
  if (help_frame   == (char *) 0) help_frame=   default_help_open_file;

  if (flags & NED_OPENF_PROMPT)
  {
    struct NED_CB_OF *cb;

    if ((cb= (struct NED_CB_OF *) calloc (sizeof (struct NED_CB_OF), 1))
        != (struct NED_CB_OF *) 0)
    {
      cb->wc= aw;
      cb->flags= flags;

      /* see * for a discussion about an alternative file open dialog */
      ned_prompt_string ("Filename: ", fnm, MAX_FNM_LENGTH,
                         help_cluster, help_frame,
                         ned_cb_open_file, (void *) cb);
    }
    return 0;
  }

  return ned_open_file_2 (aw, fnm, flags);
}
