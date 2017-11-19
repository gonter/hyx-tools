/*
 *  FILE %ned/05/ned0516.c
 *
 *  join two lines to form a single line
 *  see also: ned_join2 ()
 *
 *  written:       1991 01 28: aus NED0511.c extrahiert
 *  latest update: 2000-08-11  5:39:33
 *  $Id: ned0516.c,v 1.2 2000/08/11 03:59:16 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_join (struct LINE *lp1, struct LINE *lp2)
{
  register struct TXT *tx1;     /* line (or text) segment */
  register struct TXT *tx2;
  int lng1;                     /* length of line 1 */
  int lng2;                     /* length of line 2 */
  int lsl1= 0;                  /* line segment length */
  int lsl2;
  char *cp1= (char *) 0;
  char *cp2;
  struct FEATURE **pftr1;
  struct FEATURE  *ftr2;
  int i;

  if (lp1 == (struct LINE *) 0) return -1;
  if (lp2 == (struct LINE *) 0) return 0;     /* nichts zu tun, alles ok */

  lng1= lp1->lng;
  lng2= lp2->lng;
  if (lng1+lng2 > LINE_LNG_TXT) return -1;    /* Zeile dann zu lang ... */
  txt_adj (lng1+lng2, &lp1->txt);
  tx1= lp1->txt;                /* may be NULL */

  for (i= lng1; tx1 != (struct TXT *) 0;)
  {
    if (i < tx1->t_lng)
    {
      lsl1= tx1->t_lng-i;
      cp1= &(tx1->t[i]);
      break;
    }
    if (tx1->next == (struct TXT *) 0) break;
    i -= tx1->t_lng;
    tx1= tx1->next;
  }

  if ((tx2= lp2->txt) == (struct TXT *) 0)
  {
    lsl2= 0;
    cp2= (char *) 0;
  }
  else
  {
    lsl2= tx2->t_lng;
    cp2= tx2->t;
  }

  /* NOTE: tx1 may be NULL at this point! */
  for (i= 0; i < lng2; i++)
  {
    if (lsl1 == 0)
    {
      if ((tx1= tx1->next) == (struct TXT *) 0) break;
      lsl1= tx1->t_lng;
      cp1=  tx1->t;
    }
    if (lsl2 == 0)
    {
      if ((tx2= tx2->next) == (struct TXT *) 0) break;
      lsl2= tx2->t_lng;
      cp2=  tx2->t;
    }
    *cp1++ = *cp2++;
    lsl1--;
    lsl2--;
  }

  lp1->lng= i + lng1;

ned_message_1 ("ned0516 vor callback");
  ned_line_trigger_split_join (lp2, lp1, lng1, LCB_line_join);

#ifdef __OLD__ /* 1997-04-14  0:04:37 */
  /* Block Marker - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (lp2->line_flg & LINE_inBLOCK)
  {
    if (lp2 == b_beg.ptr || lp2 == b_end.ptr)
    {
      lp1->line_flg |= LINE_BLOCK_BEGEND;
      if (b_beg.ptr == lp2)
      {
        if (block_mode != BLOCK_MODE_box) b_beg.offset += lng1;
        b_beg.ptr= lp1;
      }

      if (b_end.ptr == lp2)
      {
        if (block_mode != BLOCK_MODE_box) b_end.offset += lng1;
        b_end.ptr= lp1;
      }
    }
  }
#endif /* __OLD__ 1997-04-14  0:04:37 */

  /* Feature Records  - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if ((ftr2= lp2->ftr) != (struct FEATURE *) 0)
  {
    for (pftr1= &lp1->ftr;
         *pftr1 != (struct FEATURE *) 0;
         pftr1= &(*pftr1)->ftr_next);

    *pftr1= ftr2;
    for (; ftr2 != (struct FEATURE *) 0; ftr2= ftr2->ftr_next)
         ftr2->ftr_pos += lng1;
    lp2->ftr= (struct FEATURE *) 0;
  }

  lp2->next= lp2->prev= (struct LINE *) 0;

  /* ASSERT: for lp2 there should be no line callbacks active now! */
#ifdef LCB_DEBUG
  ned_line_test_cb (lp2);
#endif

  ned_lines_free (lp2);

  return 0;
}
