/*
 *  FILE %ned/11/ned1111.c
 *
 *  Display all lines matching some string
 *
 *  written:       1996-10-17
 *  latest update: 1998-08-19 18:57:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_all_lines (
struct WINDOWCTRL *wc,
int use_matching_lines,         /* 1 -> use matching lines, otherwise not   */
int str_cnt,                    /* number of strings to match               */
char *mstr[])                   /* the strings themselves                   */
{
  struct LINE *lp;              /* currently examined text line             */
  int rv= 0;                    /* number of matched lines                  */

  if (str_cnt > 0) ned_message_3 ("all: '", mstr[0], "'");
  else
  {
    ned_message_1 ("all!");
    use_matching_lines= 0;
  }

  if (!use_matching_lines)
       wc->wflags &= ~HIDE_LINES;
  else wc->wflags |=  HIDE_LINES;

  for (lp= ned_find_first_line (wc->WC_act);
       lp != (struct LINE *) 0;
       lp= lp->next)
  {
    lp->line_flg &= ~LINE_HIDDEN;

/* BEGIN this section was copied from %ned/08/ned0808.c: MATCH FEATURE LINE */
      if (use_matching_lines)   /* if match strings are specified, check    */
      {                         /* check if the current feature contains    */
        int i;                  /* the given string, otherwise ignore       */
        int rc;                 /* that feature.                            */
        int matches= 0;         /* 1 -> this line matches specified string  */
        int msp, mln;
        struct LINE *mline;

        for (i= 0; i < str_cnt; i++)
        {
          rc= ned_str_match (lp, 0, lp,
                             (unsigned char *) mstr [i],
                             (unsigned char *) 0, -1,
                             &mline, &msp, &mln, 0);

          if (rc == 0)
          {
            matches= 1;
            break;
          }
        }

        if ((!matches && use_matching_lines)
            || (matches && !use_matching_lines)
           )
          lp->line_flg |= LINE_HIDDEN;
      }
/* END this section was copied from %ned/08/ned0808.c: MATCH FEATURE LINE   */
  }

  return rv;
}
