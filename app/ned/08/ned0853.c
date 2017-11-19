/*
 *  FILE %ned/08/ned0853.c
 *
 *  written:       1991 06 25
 *  latest update: 2001-02-11 12:36:58
 *  $Id: ned0853.c,v 1.2 2001/02/12 00:03:34 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int eval_logic_link (
struct WINDOWCTRL *w,           /* Window, in dem gesucht werden soll       */
char *direction)                /* Richtungsangabe des Links                */
/* return -1 ... error                                                      */
/*         0 ... not found                                                  */
/*         1 ... found, ok                                                  */
{
  struct LINE *lp;
  struct FEATURE *fp= (struct FEATURE *) 0;
  struct LINE *ftr_text;
  int lin;

  if (find_feature_with_attribute (w->WC_act, 0x0003,
        "hyx.l", "dir", direction, &lp, &lin, &fp) == 1
    ||find_feature_with_attribute (w->WC_act, 0x0003,
        "HLINK", "dir", direction, &lp, &lin, &fp) == 1)
  {
    if (fp != (struct FEATURE *) 0
        && (ftr_text= (struct LINE *) fp->ftr_text_line) != (struct LINE *) 0)
    {
      ned_eval_line (ftr_text, 1, ftr_text, ftr_text->lng -1, HYOPT_logic_link);
      return 1;
    }
  }

  return 0;
}
