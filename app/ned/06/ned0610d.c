/*
 *  FILE %ned/06/ned0610d.c
 *
 *  written:       1996-07-07
 *  latest update: 1999-04-25 16:32:10
 *  $Id: ned0610d.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_cb_open_file (char *str, void *cb_data)
{
  struct NED_CB_OF *cb;

  if ((cb= (struct NED_CB_OF *) cb_data) != (struct NED_CB_OF *) 0)
  {
    ned_open_file_2 (cb->wc, str, cb->flags);

    free (cb);
  }

  return 0;
}
