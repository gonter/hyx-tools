/*
 *  FILE %ned/03/ned0328.c
 *
 *  insert or overwrite a character in a line structure
 *
 *  written:       1991 01 29: aus ned0305.c extrahiert
 *  latest update: 1999-11-28 12:59:04
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
int qq_insert (
struct LINE *lp,        /* line structure where insertion takes place       */
int insert_idx,         /* insert position within the line                  */
int character,          /* character to insert                              */
int insert_flag)        /* 0 -> overwrite modus; 1 -> insert modus;         */
/* RETURN -1 ... error; 0 ... no update, 1 .. update                        */
{
  int i;                /* index within the TXT-segment                     */
  int sav[2];           /* buffer for shifting text ahead one character     */
  char *cpins;          /* insert position pointer                          */
  char *cp1;            /* text position 1                                  */
  char *cp2;            /* text position 2                                  */
  int lsl1;             /* line segment length 1                            */
  int lsl2;             /* line segment length 2                            */

  register struct TXT *tx1, *tx2;
  register struct FEATURE *pftr= (struct FEATURE *) 0;
  register struct FEATURE **ppftr;

  if (lp == (struct LINE *) 0) return -1;
  if (lp->line_flg & LINE_PROTECTED) return 0;

  if ((ppftr= ned_feature_find (lp, insert_idx, 1)) != (struct FEATURE **) 0)
  {
    pftr= *ppftr;
    if (pftr->ftr_edit_flags & (FTR_EDIT_NO_TEXT | FTR_EDIT_NO_INSERT))
      return 0;
  }

  sav [0]= sav [1]= 0;

  if ((tx1= lp->txt) == (struct TXT *) 0)
     tx1= lp->txt= txch_alloc (TXT_LNG, 0x20);

  for (i= insert_idx; i >= tx1->t_lng;)
  {
    i -= tx1->t_lng;
    if (tx1->next == (struct TXT *) 0
        && (tx1->next= txch_alloc (TXT_LNG, 0x20)) == (struct TXT *) 0
       )
      return -1;

    tx1= tx1->next;
  }
  cpins= &tx1->t[i];

  if (insert_flag == INSFLG_insert      /* insert mode ...                  */
      || insert_idx == lp->lng          /* ... or append at end of line     */
     )
  {
    tx2=  tx1;
    lsl1= tx1->t_lng-i;
    cp1=  cpins;
    lsl2= lsl1-1;
    cp2=  cp1 +1;

    i= insert_idx;
    sav [i % 2] = *cp1 & 0x00FF;
    for (; i < lp->lng; i++)
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
        if (tx2->next == (struct TXT *) 0)
          tx2->next= txch_alloc (TXT_LNG, 0);
        tx2=  tx2->next;
        lsl2= tx2->t_lng;
        cp2=  tx2->t;
      }

      sav [(i+1) % 2] = (*cp2) & 0x00FF;
      *cp2++= (char) sav [i % 2];
      cp1++;
      lsl1--;
      lsl2--;
    }
    lp->lng++;
  }

  *cpins= (char) character;     /* actual inserting of the character */

  if (pftr != (struct FEATURE *) 0
      && insert_flag == INSFLG_insert
      && pftr->ftr_pos < insert_idx
     )
  { /* cursor was within a displayed feature, expand that area */
    pftr->ftr_replarray_size++;
  }

  if (insert_flag == INSFLG_insert)
  {
    /* TAG_SHIFT: see * for details */
    for (pftr= lp->ftr; pftr != (struct FEATURE *) 0; pftr= pftr->ftr_next)
    {
      if (pftr->ftr_pos >= insert_idx) pftr->ftr_pos++;

#ifdef __JUNK__ /* 1996-03-10 14:32:34 */
... diese Funktion wird sowohl fuer das Inserten von normalen
Text als auch fuer Feature Segmente durch ned_wc_feature_create ()
verwendet, daher kann es zu einer Ueberschneidung des replarray
kommen, was wiederum zu unerwuenschte Effekten fuehren wuerde...

      /* EXP: 1996-03-10 13:30:03 (see: *) */
      if (pftr->ftr_pos < insert_idx
          && pftr->ftr_pos + pftr->ftr_replarray_size-1 >= insert_idx
         )
        pftr->ftr_replarray_size++;
#endif /* __JUNK__ 1996-03-10 14:32:34 */
    }

    ned_line_trigger_change (lp, insert_idx, 1);
  }

  return 1;
}
