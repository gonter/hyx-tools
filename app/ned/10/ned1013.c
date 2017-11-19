/*
 *  FILE %ned/10/ned1013.c
 *
 *  define button
 *
 *  written:       1992 04 04
 *  latest update: 1999-04-25 16:36:32
 *  $Id: ned1013.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

extern struct BUTTON_DESCRIPTOR *buttons;

/* ------------------------------------------------------------------------ */
int def_button (
int bdx,
int bdy,
int bdc,
int bdt,
int bdm,
int bdi,
char *bdtext)
{
  struct BUTTON_DESCRIPTOR *bd;

  if ((bd= (struct BUTTON_DESCRIPTOR *)
           calloc (sizeof (struct BUTTON_DESCRIPTOR), 1))
      != (struct BUTTON_DESCRIPTOR *) 0)
  {
    bd->BD_x= bdx;
    bd->BD_y= bdy;
    bd->BD_id= bdi;
    bd->BD_colour= bdc;
    bd->BD_type= bdt;
    bd->BD_macro_num= bdm;
    bd->BD_text= strdup (bdtext);

    bd->BD_next= buttons;
    buttons= bd;
  }

  return 0;
}
