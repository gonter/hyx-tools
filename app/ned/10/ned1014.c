/*
 *  FILE %ned/10/ned1014.c
 *
 *  locate a button
 *
 *  written:       1992 04 04
 *  latest update: 1997-10-26 10:23:04
 *  $Id: ned1014.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

extern struct BUTTON_DESCRIPTOR *buttons;

/* ------------------------------------------------------------------------ */
struct BUTTON_DESCRIPTOR *locate_button (int bdx, int bdy)
{
  struct BUTTON_DESCRIPTOR *bd;

  for (bd= buttons; bd != (struct BUTTON_DESCRIPTOR *) 0; bd= bd->BD_next)
  {
    if (bdy == bd->BD_y
        && bdx >= bd->BD_x
        && bdx < bd->BD_x + strlen (bd->BD_text)
       )
      return bd;
  }

  return (struct BUTTON_DESCRIPTOR *) 0;
}
