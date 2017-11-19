/*
 *  FILE %ned/08/ned0809.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  written:       1987 09 08
 *                 1991 02 03: Revision
 *                 1991 09 03: Revision
 *  latest update: 1998-08-16 12:32:19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;
extern struct WINDOWCTRL *aw;
extern int oper_level;

/* ------------------------------------------------------------------------ */
int ned_setup_feature_window (
int ftr_types,                  /* range of features to include             */
int ftr_subtypes,               /* range of subtypes if available           */
int str_cnt,                    /* number of strings to match               */
char *mstr[])                   /* the strings themselves                   */
{
  struct WINDOWCTRL *fw;
  struct WINDOWCTRL *ow;
  struct WINDOWCTRL *w2;

  if (oper_level >= LEV_LINK
      || (ow= aw) == (struct WINDOWCTRL *) 0
      || ow->file_or_frame == (void *) 0
      || ow->file_type == FTY_FTRWDW
      || (fw= ow->feature_window) == (struct WINDOWCTRL *) 0
      /* || fw->page == 0 ################### */
     ) return -1;

  if ((w2= active_feature_window (ow)) != (struct WINDOWCTRL *) 0)
  {
    struct LINE *l;
    struct FEATURE *f;

    ned_message_1 ("jumping to active feature window!");
    q2_jmpwdw (w2);
    q0_jmpwdw (w2);
    if ((f= ow->WC_act->ftr) != (struct FEATURE *) 0
       && (l= (struct LINE *) f->ftr_text_line) != (struct LINE *) 0)
      aw->WC_act= l;
  }
  else
  {
    if (ned_link_feature_lines (ftr_types, ftr_subtypes, str_cnt, mstr) == 0)
      return -1;                        /* keine Features im Window !!      */

    q_jmpwdw (p_wdwopen ());            /* das setzt aw neu!!!              */

    /* Link to Feature Window */
    wdw_rst (aw);
    aw->WC_first= fw->WC_first;
    aw->WC_act= fw->WC_act;
    fw->page= 0;
    aw->file_type= FTY_FTRWDW;
    aw->WC_edit_mode= EDIT_NOLINEOPS;
    aw->feature_window= ow;
  }

  ned_w_jmp_aktline (aw, NEDJMP_LINE_MID, 0, NEDJMP_FLAG_REDRAW);

  return 0;
}
