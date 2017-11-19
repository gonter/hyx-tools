/*
 *  FILE %ned/08/ned0886.c
 *
 *  written:       1996-03-07
 *  latest update: 2001-02-11 11:13:09
 *  $Id: ned0886.c,v 1.4 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdlib.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

#define MAX_BUFFER1  160

/* ------------------------------------------------------------------------ */
struct FEATURE *ned_feature_set (
struct WINDOWCTRL *w,
struct LINE *lp,
int offset,
int what,
int ftr_segment_cnt,
const char *ftr_segment [])
{
  struct FEATURE *fp;
  struct LINE *lp_ftr;
  char *buffer1a;
  char *buffer1b;
  int repl_size;

  if ((fp= q_feature_set (lp, offset, what, ftr_segment_cnt, ftr_segment))
        == (struct FEATURE *) 0
      || (lp_ftr= fp->ftr_text_line) == (struct LINE *) 0
      || (buffer1a= malloc (MAX_BUFFER1)) == (char *) 0
     ) return (struct FEATURE *) 0;

  if (ned_line_2_string (lp_ftr, 0, lp_ftr, lp_ftr->lng, buffer1a, MAX_BUFFER1,
                     0L, 0x0000) != (char *) 0
      && (buffer1b= malloc (MAX_BUFFER1)) != (char *) 0
     )
  {
    ned_message_1 (buffer1a);
    ned_identify_feature (w, lp, offset, what, fp,
                          buffer1a, buffer1b, &repl_size, MAX_BUFFER1);

    free (buffer1b);
  }

  free (buffer1a);

  w->f_upd= 1;

  return fp;
}

/* ------------------------------------------------------------------------ */
struct FEATURE *ned_feature_set2 (
struct WINDOWCTRL *w,
int line,
int offset,
int what,
int ftr_segment_cnt,
const char *ftr_segment [])
{
  struct FEATURE *f;
  struct LINE *l;
  int l_jmp;

  if (w == (struct WINDOWCTRL *) 0
      || (l_jmp= line) <= 0
      || (l= ned_get_line_by_nr (w->WC_act, &l_jmp)) == (struct LINE *) 0
      || l_jmp != line
     )
     return (struct FEATURE *) 0;

  return ned_feature_set (w, l, offset, what, ftr_segment_cnt, ftr_segment);
}
