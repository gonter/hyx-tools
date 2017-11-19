/*
 *  FILE %ned/03/ned0303.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1999-04-25 16:30:34
 *  $Id: ned0303.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

#ifdef USE_ABBREVIATIONS
#include <stdlib.h>
#include <string.h>
#include <gg/ytree.h>
#endif /* USE_ABBREVIATIONS */

extern int key;

/* ------------------------------------------------------------------------ */
#ifdef USE_ABBREVIATIONS
extern struct WINDOWCTRL *aw;

static struct YTREE *abbreviations= (struct YTREE *) 0;

#define MAX_LHS 50
static char LHS [MAX_LHS];
static int LHS_cnt= 0;
#endif /* USE_ABBREVIATIONS */

/* ------------------------------------------------------------------------ */
void p_ins ()
{
  int ch;

  ch= key;

#ifdef USE_ABBREVIATIONS
  if ((ch >= 'A' && ch <= 'Z')
      || (ch >= 'a' && ch <= 'z')
      || (ch >= '0' && ch <= '9')
      || ch == '_'
     )
  {
    if (LHS_cnt < MAX_LHS) LHS [LHS_cnt++]= (char) ch;
  }
  else
  {
    ned_check_abbrev ();
  }
#endif /* USE_ABBREVIATIONS */

  q_insert (ch, 1);
}

/* ------------------------------------------------------------------------ */
#ifdef USE_ABBREVIATIONS
int ned_check_abbrev ()
{
  char *rhs;
  struct WINDOWCTRL *wc;
  int rc= 0;
  int insf;

  if (LHS_cnt > 0
      && LHS_cnt < MAX_LHS
      && (wc= aw) != (struct WINDOWCTRL *) 0
     )
  {
    LHS [LHS_cnt]= 0;
    if ((rhs= (char *) ytree_get_value (abbreviations, (unsigned char *) LHS))
              != (char *) 0
       )
    {
      wc->cx -= LHS_cnt;
      insf= wc->ins_flg;
      wc->ins_flg= INSFLG_insert;

      qq_delete (wc->WC_act, wc->hv + wc->cx - wc->ax, LHS_cnt);
      ned_paste_string (rhs, 1, (char *) 0, (char *) 0);
      wc->ins_flg= insf;
      rc= 1;
    }
  }

  LHS_cnt= 0;

  return rc;
}

/* ------------------------------------------------------------------------ */
int ned_reset_abbrev ()
{
  LHS_cnt= 0;
  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_abbrev_reduce ()
{
  if (LHS_cnt) LHS_cnt--;
  return LHS_cnt;
}

/* ------------------------------------------------------------------------ */
int ned_define_abbrev (const char *lhs, const char *rhs)
{
  char *old_rhs;
  int rc= 0;

  if (lhs == (char *) 0 || *lhs == 0
      || rhs == (char *) 0 || *rhs == 0
     ) return -1;

  if ((old_rhs= (char *) ytree_get_value (abbreviations,
                                          (unsigned char *) lhs))
                != (char *) 0)
  {
    free (old_rhs);
    rc= 1;
  }

  ytree_set_value (&abbreviations, (unsigned char *) lhs,
                   (long) strdup (rhs));

  return rc;
}

/* ------------------------------------------------------------------------ */
int ned_undefine_abbrev (const char *lhs)
{
  char *old_rhs;
  int rc= 0;

  if (lhs == (char *) 0 || *lhs == 0) return -1;

  if ((old_rhs= (char *) ytree_get_value (abbreviations,
                                          (unsigned char *) lhs))
                != (char *) 0)
  {
    free (old_rhs);
    ytree_delete_word (&abbreviations, (unsigned char *) lhs);
    rc= 1;
  }

  return rc;
}

#endif /* USE_ABBREVIATIONS */
