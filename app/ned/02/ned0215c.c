/*
 *  FILE %ned/02/ned0215c.c
 *
 *  create a feature window
 *
 *  written:       1995-09-23
 *  latest update: 1999-04-25 16:30:18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct WINDOWCTRL *ned_create_window_pair ()
{
  register struct WINDOWCTRL *w_new;
  register struct WINDOWCTRL *w_ftr;

  if ((w_new= ned_create_editor_window ()) != (struct WINDOWCTRL *) 0)
  {
    if ((w_ftr= ned_create_feature_window ()) != (struct WINDOWCTRL *) 0)
    {
      w_new->feature_window= w_ftr;
    }
    else
    {
      free (w_new);
      w_new= (struct WINDOWCTRL *) 0;
    }
  }

  return w_new;
}
