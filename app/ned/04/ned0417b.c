/*
 *  FILE %ned/04/ned0417b.c
 *
 *  link two windows
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1995-10-30: extracted from ned0417.c
 *  latest update: 2000-12-09 13:16:07
 *  $Id: ned0417b.c,v 1.2 2000/12/09 17:33:10 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int q2_link (
struct WINDOWCTRL *w_dest,
struct WINDOWCTRL *w_src,
int flags)
{
  ned_lines_free (w_dest->first);
  wdw_rst (w_dest);

  /* Link Count erhoehen */
  w_dest->file_or_frame= w_src->file_or_frame;
  if ((w_dest->file_type= w_src->file_type) == FTY_HYPER)
       ((struct FRAMECTRL *) w_dest->file_or_frame)->links++;
  else ((struct FILECTRL *) w_dest->file_or_frame)->FC_links++;

  w_dest->WC_title_short= strdup_or_what (w_src->WC_title_short);
  w_dest->WC_title_long=  strdup_or_what (w_src->WC_title_long);

#ifdef USE_TK
  ned_tk_set_window_name (w_dest, w_dest->WC_title_short);
#endif /* USE_TK */

  w_dest->first= w_dest->WC_act= w_src->WC_act;
  ned_w_jmp_aktline (w_dest, NEDJMP_LINE_3, 0, flags);

  return 0;
}
