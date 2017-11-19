/*
 *  FILE %ned/02/ned0260.c
 *
 *  Marker Handling
 *
 *  written:       1996-05-27
 *  latest update: 1999-04-25 16:30:30
 *  $Id: ned0260.c,v 1.3 2003/10/02 06:45:51 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>      /* DEBUG ONLY */
#include "ed.h"
#include "proto.h"

#ifdef UX_DEBUG
#include <stdio.h>
#endif

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
extern struct MARKER b_beg, b_end;
extern struct MARKER b_first, b_last;
extern int block_mode;

#define NUM_MARKER 128
static struct MARKER **marker_list= (struct MARKER **) 0;

/* ------------------------------------------------------------------------ */
struct MARKER *ned_get_marker (int marker_id, int alloc)
{
  if (marker_id == '[' || marker_id == '{'
      || marker_id == '(' || marker_id == '<'
     )
  {
    return &b_beg;
  }

  if (marker_id == ']' || marker_id == '}'
      || marker_id == ')' || marker_id == '>'
     )
  {
    return &b_end;
  }

  if (marker_id == '`') marker_id= '\'';

  if (marker_list == (struct MARKER **) 0 && alloc)
    marker_list= calloc (sizeof (struct MARKER *), NUM_MARKER);

  if (marker_list != (struct MARKER **) 0
      && marker_id >= 0x00 && marker_id < NUM_MARKER)
  {
    struct MARKER *mp;

    if ((mp= marker_list [marker_id]) == (struct MARKER *) 0 && alloc)
      mp= marker_list [marker_id]= calloc (sizeof (struct MARKER), 1);

    return mp;
  }

  return (struct MARKER *) 0;
}

/* ------------------------------------------------------------------------ */
/* adjust offset of marker on the line to the right of idx by cnt byte.     */
int ned_marker_callback (
int event,
void *line,
void *cd,
int column,
void *op2)
{
  struct MARKER *mp;
  int i;

#ifdef MSDOS
  line;
#endif

#ifdef UX_DEBUG
  printf (
    "0260 ned_marker_callback (event=%d, line=%08lX, cd=%08lX, col=%d op2=%08lX)\n",
    event, line, cd, column, op2);
#endif

  if ((mp= (struct MARKER *) cd) == (struct MARKER *) 0) return -1;

  switch (event)
  {
    case LCB_edit:
      if (mp->offset > column) mp->offset += (int) op2;
      break;

    case LCB_delete:
      /* 1997-06-18 12:40:48 Fix fuer crash beim Aufruf von p_blkbeg() ?? */
      if (mp == &b_beg || mp == &b_end || mp == &b_first || mp == &b_last)
      {
        mp->wptr= (struct WINDOWCTRL *) 0;
        mp->ptr= (struct LINE *) 0;
        break;
      }

      if (marker_list != (struct MARKER **) 0)
        for (i= 0; i < NUM_MARKER; i++)
        {
          if (mp == marker_list [i])
          {
            free (mp);
            marker_list [i]= (struct MARKER *) 0;
            break;
          }
        }
      break;

    case LCB_line_split:
      if (mp->offset >= column)
      {
        struct LINE *nl, *pl;

        nl= (struct LINE *) op2;
        pl= mp->ptr;

        /*** BEGIN block marker handling ***/
        if (mp == &b_beg)
        {
          if (column <= b_beg.offset)
          {
            nl->line_flg |= LINE_BLOCK_BEGEND;
            pl->line_flg &= LINE_BLOCK_CLR;
          }
          else nl->line_flg |= LINE_BLOCK_INBLOCK;
        }

        if (mp == &b_end)
        {
          if (column < b_end.offset)
          {
            nl->line_flg |= LINE_BLOCK_BEGEND;
            pl->line_flg &= LINE_BLOCK_CLR_BEGEND;
            pl->line_flg |= LINE_BLOCK_INBLOCK;
          }
          else pl->line_flg &= LINE_BLOCK_CLR;
        }
        /*** END block marker handling ***/

        mp->ptr= nl;
        mp->offset -= column;

        ned_marker_reg_cb (nl, mp);
      }
      return 1;

    case LCB_line_join:
{
  char bu [40];
  sprintf (bu, "column= %d", column);
ned_message_2 ("marker cb: join; ", bu);
}

      mp->ptr= (struct LINE *) op2;
      mp->offset += column;

      ned_marker_reg_cb (mp->ptr, mp);
      return 1;

    case LCB_chg_wdw:
      mp->wptr= (struct WINDOWCTRL *) op2;
      return 0;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
/* Reset all markers that belong to the given window.                       */
/* If the window is NULL, all markers have to be reset.                     */
int ned_reset_markers (struct WINDOWCTRL *w)
{
  struct MARKER *mp;
  int i;

  if (w == (struct WINDOWCTRL *) 0
      || b_beg.wptr == w
      || b_end.wptr == w
      || b_first.wptr == w              /* T2D: thats paranoid */
      || b_last.wptr == w
     ) ned_blk_rst ();

  if (marker_list != (struct MARKER **) 0)
    for (i= 0; i < NUM_MARKER; i++)
    {
      if ((mp= marker_list [i]) != (struct MARKER *) 0
          && (w == (struct WINDOWCTRL *) 0 || mp->wptr == w)
         )
      {
        free (mp);
        marker_list [i]= (struct MARKER *) 0;
      }
    }

  return 0;
}

/* ------------------------------------------------------------------------ */
/* Reset a specified marker                                                 */
int ned_reset_a_marker (int marker_id)
{
  struct MARKER *mp;

  if (marker_list != (struct MARKER **) 0
      && marker_id >= 0x00 && marker_id < NUM_MARKER
      && (mp= marker_list [marker_id]) != (struct MARKER *) 0
     )
  {
    free (mp);
    marker_list [marker_id]= (struct MARKER *) 0;
    return 1;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
/* Reset a specified marker                                                 */
int ned_check_for_markers (struct LINE *lp, int all)
{
  struct MARKER *mp;
  int marker_id;

  if (marker_list == (struct MARKER **) 0) return -1;

  while (lp != (struct LINE *) 0)
  {
    for (marker_id= 0; marker_id < NUM_MARKER; marker_id++)
      if ((mp= marker_list [marker_id]) != (struct MARKER *) 0
          && mp->ptr == lp
         )
      {
        fprintf (stderr,
         "0260: marker %c (0x%02X) found on line %08lX unexpectedly!\n",
         marker_id,
         (marker_id > ' ' && marker_id < 0x7F) ? marker_id : '.',
         lp
         );
      }

    lp= lp->next;

    if (lp != (struct LINE *) 0 && !all)
    {
      fprintf (stderr, "0260: lp->next is not NULL!\n");
    }
  }

  return 0;
}
