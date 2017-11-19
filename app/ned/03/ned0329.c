/*
 *  FILE %ned/03/ned0329.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1991 01 29: aus NED0306.C extrahiert
 *  latest update: 1997-08-28  7:09:12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int qq_delete (
struct LINE *lp,
int delete_idx,
int delete_cnt)
/* RETURN: -1 .. erorr; 0 .. no update; 1 .. update */
{
  int i;                /* Index innerhalb der Zeile */
  int lsl1;
  int lsl2;
  char *cp1;
  char *cp2;

  register struct TXT *tx1, *tx2;
  register struct FEATURE *pftr= (struct FEATURE *) 0;
  register struct FEATURE **ppftr;

  if (lp == (struct LINE *) 0) return -1;
  if (lp->line_flg & LINE_PROTECTED) return 0;

  if ((ppftr= ned_feature_find (lp, delete_idx, 1)) != (struct FEATURE **) 0)
  {
    pftr= *ppftr;
    if (pftr->ftr_edit_flags & (FTR_EDIT_NO_TEXT | FTR_EDIT_NO_INSERT))
      return 0;
  }

  if ((tx2= tx1= lp->txt) == (struct TXT *) 0) return -1;

  /* Positionierung des Destination Pointers */
  for (i= delete_idx; i >= tx1->t_lng;)
  {
    i -= tx1->t_lng;
    if (tx1->next == (struct TXT *) 0) return 0;
    tx1= tx1->next;
  }

  cp1= &tx1->t [i];
  lsl1= tx1->t_lng-i;

  /* Positionierung des Source Pointers */
  for (i= delete_idx+delete_cnt; i >= tx2->t_lng;)
  {
    i -= tx2->t_lng;
    if (tx2->next == (struct TXT *) 0) goto DONE;
    tx2= tx2->next;
  }
  cp2= &tx2->t[i];
  lsl2= tx2->t_lng-i;

  for (i= lp->lng - delete_idx - delete_cnt; i > 0; i--)
  {
    if (lsl1 == 0)
    {
      if (tx1->next == (struct TXT *) 0) break;
      tx1=  tx1->next;
      lsl1= tx1->t_lng;
      cp1=  tx1->t;
    }

    if (lsl2 == 0)
    {
      if (tx2->next == (struct TXT *) 0) break;
      tx2=  tx2->next;
      lsl2= tx2->t_lng;
      cp2=  tx2->t;
    }

    *cp1++= *cp2++;
    lsl1--;
    lsl2--;
  }

DONE:
  txt_adj (lp->lng -= delete_cnt, &lp->txt);

  if (pftr != (struct FEATURE *) 0
      && pftr->ftr_pos < delete_idx
     )
  { /* cursor was within a displayed feature, shrink that area */
    pftr->ftr_replarray_size -= delete_cnt;
  }

  /* Anpassung von Markern und Features */
  for (pftr= lp->ftr; pftr != (struct FEATURE *) 0; pftr= pftr->ftr_next)
      if (pftr->ftr_pos > delete_idx) pftr->ftr_pos -= delete_cnt;

  ned_line_trigger_change (lp, delete_idx, -delete_cnt);

  return 1;
}
