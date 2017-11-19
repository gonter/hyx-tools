/*
 *  FILE %ned/08/ned0808.c
 *
 *  int ned_link_feature_lines (void)
 *    Verkettet alle Feature Zeilen eines Windows und ordnet diese
 *    Kette dem Feature Window des aktuellen Windows zu.
 *    Die aktuelle Zeile des Windows wird auf das Feature gesetzt,
 *    welches an der aktuellen Cursor Position ist (oder am naechsten
 *    dazu ist??)
 *    Falls Match-Strings angegeben sind (str_cnt > 0), dann werden
 *    nur solche Feature Lines beruecksichtigt, die den String enthalten.
 *    Letzteres Feature wird dazu verwendet, um nur Tags eines bestimmten
 *    Typs anzuzeigen.
 *
 *  written:       1987 09 08
 *                 1991 02 07: Revision
 *                 1991 05 29: Revision
 *  latest update: 1997-01-06 11:11:02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_link_feature_lines (    /* Feature Text verketten                   */
int ftr_types,                  /* range of features to include             */
int ftr_subtypes,               /* range of subtypes if available           */
int str_cnt,                    /* number of strings to match               */
char *mstr[])                   /* the strings themselves                   */
{
  struct LINE *lp;              /* currently examined text line             */
  struct LINE *lpf;             /* letzte Feature Zeile bei Verkettung      */
  struct LINE *lp_ftr;          /* text line of the feature record          */
  struct FEATURE *ft;           /* Features                                 */
  struct WINDOWCTRL *fw;        /* Feature Window                           */
  int flg_ftr= 0;               /* 1 -> aktuelles Window hat Feautres       */
  int flg_akt= 0;               /* 1 -> aktuelle Zeile hat Feature          */
  int curx;                     /* Spalte in der sich der Cursor befindet   */

  if ((lp= ned_find_first_line (aw->first)) == (struct LINE *) 0) return -1;

  curx= aw->cx + aw->hv - aw->ax;
  fw= aw->feature_window;

  fw->first= (struct LINE *) 0;

  lpf= (struct LINE *) 0;
  for (; lp != (struct LINE *) 0; lp= lp->next)
  {
    for (ft= lp->ftr; ft != (struct FEATURE *) 0; ft= ft->ftr_next)
    {
      /* check if this feature is to be used at all */
      if ((ftr_types != 0 && ftr_types != ft->ftr_type)
          || (ftr_subtypes != 0 && ftr_subtypes != ft->ftr_type)
         ) continue;

      /* MATCH FEATURE LINE - - - - - - - - - - - - - - - - - - - - - - - - */
      if (str_cnt > 0)          /* if match strings are specified, check    */
      {                         /* check if the current feature contains    */
        int i;                  /* the given string, otherwise ignore       */
        int rc;                 /* that feature.                            */
        int matches= 0;         /* 1 -> this line matches specified string  */
        int msp, mln;
        struct LINE *mline;
        struct LINE *aline;

        aline= (struct LINE *) ft->ftr_text_line;
        for (i= 0; i < str_cnt; i++)
        {
          rc= ned_str_match (aline, 0, aline,
                             (unsigned char *) mstr [i],
                             (unsigned char *) 0, -1,
                             &mline, &msp, &mln, 0);
          if (rc == 0)
          {
            matches= 1;
            break;
          }
        }

        if (!matches) continue;
      }

      /* doppelte Verkettung */
      lp_ftr= (struct LINE *) ft->ftr_text_line;
      lp_ftr->prev= lpf;
      if (lpf != (struct LINE *) 0) lpf->next= lp_ftr;

      /* check, if this feature can be edited or not */
      if (ft->ftr_edit_flags & FTR_EDIT_NO_EDIT)
        lp_ftr->line_flg |= LINE_PROTECTED;

      /* Cursor Placement */
      if (flg_akt == 0) fw->first= fw->WC_act= lp_ftr;

      if (lp == aw->WC_act)
      {
        if (flg_akt == 0) fw->first= lp_ftr;
        if (flg_akt == 0 || (flg_akt == 1 && ft->ftr_pos <= curx))
        {
          fw->WC_act= lp_ftr;
          flg_akt= 1;
        }
        if (ft->ftr_pos >= curx) flg_akt= 2;
      }

      lpf= lp_ftr;
      flg_ftr= 1;
    }
  }

  return flg_ftr;
}
