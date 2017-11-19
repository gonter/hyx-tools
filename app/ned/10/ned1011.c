/*
 *  FILE %ned/10/ned1011.c
 *
 *  setup button definiton
 *
 *  written:       1992 04 04
 *  latest update: 1999-04-25 16:36:28
 *  $Id: ned1011.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

extern struct BUTTON_DESCRIPTOR *buttons;

/* ------------------------------------------------------------------------ */
int rst_button ()
{
  struct BUTTON_DESCRIPTOR *bd;
  struct BUTTON_DESCRIPTOR *bd2;

  for (bd= buttons; (bd2= bd) != (struct BUTTON_DESCRIPTOR *) 0;)
  {
    bd= bd->BD_next;
    free (bd2->BD_text);
    free (bd2);
  }

  return 0;
}
