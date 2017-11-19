/*
 *  FILE %ned/05/ned0515.c
 *
 *  split a line into two new lines
 *
 *  written:       1991 01 27: extracted from ned0509.c
 *                 1991 10 13: revision: block flags
 *  latest update: 2001-09-28 16:47:13
 *  $Id: ned0515.c,v 1.3 2001/09/28 18:48:28 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
int ned_split (                         /* split a line into two lines      */
struct LINE  *split_line,               /* line to be splitted              */
struct LINE **splitted_part,            /* line created after splitting     */
int split_position,                     /* position where splitting is done */
int auto_indent)                        /* 1 -> auto indent for new line    */
/* RETURN: -1 ... error                                                     */
/*         >= 0 ... number of padded blanks, when auto indent was done      */
{
  int line_length;                      /* length of line to be splitted    */
  int bai= 0;                           /* number of blanks for auto indent */
  register struct LINE *nl;             /* newly created line               */
  register struct TXT  *tx1;            /* text segments in old line        */
  register struct TXT  *tx2;            /* text segments in new line        */
  int lsl1;                             /* line segment length for line 1   */
  int lsl2= 0;                          /* line segment length for line 2   */
  char *cp1;                            /* text segment pointer for line 1  */
  char *cp2;                            /* text segment pointer for line 2  */
  struct FEATURE *ftr1;                 /* features are re-aranged too      */
  struct FEATURE **pftr1;
  struct FEATURE **pftr2;
  int i;

  *splitted_part= (struct LINE *) 0;
  if (split_line == (struct LINE *) 0   /* undefined line ...               */
      || split_position < 0             /* ... or split position            */
      || (split_line->line_flg & LINE_PROTECTED)
     )
    return -1;                          /* result in an error               */

  /* T2D: check if cursor is on a feature replace array and deal            */
  /*      with it accordingly.                                              */

  line_length= split_line->lng;
  if (split_position > line_length) split_position= line_length;
  if ((nl= alloc_line ()) == (struct LINE *) 0) return -1;

  /* Note: when the line to be splitted is empty we get another empty line. */
  if ((tx1= split_line->txt) != (struct TXT *) 0)
  {
    lsl1= tx1->t_lng;
    cp1= tx1->t;
    if (auto_indent)
    {
      while (bai < line_length)         /* erstes Zeichen != BLANK suchen   */
      {
        if (lsl1 == 0)
        {
          if ((tx1= tx1->next) == (struct TXT *) 0) break;
          lsl1= tx1->t_lng;
          cp1= tx1->t;
        }
        if (*cp1 != 0x20) break;
        cp1++;
        lsl1--;
        bai++;
      }
      if (bai >= split_position)
        bai= 0;                         /* Auto Indent nach                 */
                                        /* Leerzeilen vermeiden             */
      if ((tx1= split_line->txt) != (struct TXT *) 0)
      {
        lsl1= tx1->t_lng;
        cp1= tx1->t;
      } /* else ???? ### (1994-12-27/20:20) */
    }

    txt_adj (bai+1, &nl->txt);          /* create a new line with the right */
                                        /* number of blanks.                */
    tx2= nl->txt;
    cp2= tx2->t;                        /* should not be necessary...       */

    for (i= bai;;)                      /* search for character insert      */
    {                                   /* position in splitted part.       */
      if (i < tx2->t_lng)
      {
        lsl2= tx2->t_lng-i;
        cp2= &(tx2->t[i]);
        break;
      }
      if (tx2->next == (struct TXT *) 0) break;
      i -= tx2->t_lng;
      tx2= tx2->next;
    }

    for (i= split_position;;)           /* search for character transfer    */
    {                                   /* position in original line.       */
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

    for (i= 0; i+split_position < line_length; i++)
    {
      if (lsl2 == 0)
      {
        if (tx2->next == (struct TXT *) 0)
            tx2->next= txch_alloc (TXT_LNG, 0x20);
        tx2= tx2->next;
        if (tx2 == (struct TXT *) 0) return -1;
        lsl2= tx2->t_lng;
        cp2= tx2->t;
      }
      if (lsl1 == 0)
      {
        if ((tx1= tx1->next) == (struct TXT *) 0) break;
        lsl1= tx1->t_lng;
        cp1= tx1->t;
      }
      *cp2++= *cp1++;
      lsl1--;
      lsl2--;
    }

    txt_adj (split_line->lng= split_position, &split_line->txt);
    txt_adj (nl->lng= i+bai, &nl->txt);
  }

  if ((split_line->line_flg & LINE_inBLOCK) == LINE_BLOCK_INBLOCK)
    nl->line_flg |= LINE_BLOCK_INBLOCK;
  /* Note: if line is begin or end, the callback function does the rest */

  ned_line_trigger_split_join (split_line, nl,
                               split_position, LCB_line_split);

#ifdef __T2D__ /* 1997-04-13 21:27:19 */
NOTE: these code particles should be moved into the marker callback
      function

  /* Block Flags  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (split_line->line_flg & LINE_inBLOCK)
  {
    if (split_line == b_beg.ptr)
    {
      if (split_position <= b_beg.offset)
      {
#ifdef __OLD__ /* 1997-04-23 18:29:28 */
        b_beg.ptr= nl;
        if (block_mode != BLOCK_MODE_box) b_beg.offset -= split_line->lng;
#endif /* __OLD__ 1997-04-23 18:29:28 */
        nl->line_flg |= LINE_BLOCK_BEGEND;
        split_line->line_flg &= LINE_BLOCK_CLR;
      }
      else nl->line_flg |= LINE_BLOCK_INBLOCK;
    }

    if (split_line == b_end.ptr)
    {
      if (split_position < b_end.offset)
      {
#ifdef __OLD__ /* 1997-04-23 18:29:28 */
        b_end.ptr= nl;
        if (block_mode != BLOCK_MODE_box) b_end.offset -= split_line->lng;
#endif /* __OLD__ 1997-04-23 18:29:28 */
        nl->line_flg |= LINE_BLOCK_BEGEND;
        split_line->line_flg &= LINE_BLOCK_CLR_BEGEND;
        split_line->line_flg |= LINE_BLOCK_INBLOCK;
      }
      else split_line->line_flg &= LINE_BLOCK_CLR;
    }

    if (!(split_line->line_flg & LINE_BLOCK_BEGEND))
      nl->line_flg |= LINE_BLOCK_INBLOCK;
  }
#endif /* __T2D__ 1997-04-13 21:27:19 */

  /* Feature Records  - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  pftr2= &nl->ftr;
  for (pftr1= &split_line->ftr; (ftr1= *pftr1) != (struct FEATURE *) 0;)
  {
    if (ftr1->ftr_pos >= split_position)
    {
      ftr1->ftr_pos= ftr1->ftr_pos - split_position + bai;
      *pftr2= ftr1;
      *pftr1= ftr1->ftr_next;
      pftr2= &ftr1->ftr_next;
      *pftr2= (struct FEATURE *) 0;
    }
    else pftr1= &ftr1->ftr_next;
  }

  /* Carriage Return Flag uebernehmen - - - - - - - - - - - - - - - - - - - */
  if (split_line->line_flg & LINE_CODE_0x0D)
     nl->line_flg |= LINE_CODE_0x0D;

  *splitted_part= nl;

  return bai;
}
