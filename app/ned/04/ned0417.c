/*
 *  FILE %ned/04/ned0417.c
 *
 *  prompt for a window number to link to
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1995-10-30: extracted parts to ned0417b.c
 *  latest update: 1998-08-16 12:27:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "edhyx.h"
#include <gg/window.h>
#include "proto.h"

extern struct WINDOWCTRL *aw, *windows;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_link ()                       /* ^KL: Link to File at Window         */
{
  int k;
  struct WINDOWCTRL *w;

  if (oper_level >= LEV_LINK) return;
  if (aw->file_or_frame != (void *) 0) return;

  /* setchar (2, 0, 'L'); ??? */
  ned_message_1 ("Link current Window to Window #");

  k= q_window_menu ();

  if (k <= 0) return;
  k--;

  w= windows;
  while (k-- && w != (struct WINDOWCTRL *) 0) w= w->next;

  if (w == (struct WINDOWCTRL *) 0      /* window not found                 */
      || w == aw                        /* or link to itself                */
     ) return;                          /* is not such a smart idea         */

  q2_link (aw, w, NEDJMP_FLAG_REDRAW);
}
