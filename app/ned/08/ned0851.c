/*
 *  FILE %ned/08/ned0851.c
 *
 *  see docu
 *
 *  written:       1991 06 25
 *  latest update: 1997-07-27 11:37:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/hyx.h>
#include <gg/dpp.h>
#include "ed.h"
#include "proto.h"
#ifdef USE_TK
#include <tcl.h>
#include <tk.h>
#include "edtcl.h"
#include "edtk.h"
#endif /* USE_TK */

#define LIN_SIZ 80

/* ------------------------------------------------------------------------ */
int eval_window_parameters (
struct WINDOWCTRL *w,           /* window to be modified                    */
char *str)                      /* window parameters in string              */
/* return -1 ... error                                                      */
/*         0 ... no parameters found                                        */
/*         Bit 0: ... window parameters found                               */
/*         Bit 1: ... ln-parameters found                                   */
/*         Bit 2: ... mark-paramter found                                   */
{
  int rc= 0;
  int ln, cn;
  char txt [LIN_SIZ];
  struct LINE *lp;
  struct FEATURE *fp;

  if (find_attr_value (str, txt, LIN_SIZ, "ln") != -1)
  {
    ln= (int) get_parameter_value (txt);
    ned_jmp_2line_by_nr (w, ln, 0x00);
    rc |= 0x0002;
  }

  if (find_attr_value (str, txt, LIN_SIZ, "mark") != -1
      && (find_feature_with_attribute (w->WC_act, 0x0003,
              "hyx.l", "name", txt, &lp, &ln, &fp) == 1
          || find_feature_with_attribute (w->WC_act, 0x0003,
              "mark", "id", txt, &lp, &ln, &fp) == 1
         )
     )
  {
    ned_jmp_2line_by_nr (w, ln, 0x00);
    jmp2column (w, fp->ftr_pos);
    rc |= 0x0004;
  }

  if (find_attr_value (str, txt, LIN_SIZ, "cn") != -1)
  {
    cn= (int) get_parameter_value (txt);
    jmp2column (w, cn);
  }

#ifdef USE_TK
  if (w->wc_taint_level == 0)
  {
    if (find_attr_value (str, txt, LIN_SIZ, "cmd_right_button") != -1)
      ned_tk_setup_special (w, NED_TK_CMD_MOUSE_B2, txt);

    if (find_attr_value (str, txt, LIN_SIZ, "cmd_menu") != -1)
      ned_tk_setup_special (w, NED_TK_CMD_MENU, txt);

    if (find_attr_value (str, txt, LIN_SIZ, "cmd_wins") != -1)
      ned_tk_setup_special (w, NED_TK_CMD_WINS, txt);
  }
#endif /* USE_TK */

  return rc;
}
