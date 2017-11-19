/*
 *  FILE %ned/10/ned1018.c
 *
 *  Maus Steuerung
 *
 *  written:       1988 09 04
 *                 1990 01 20: Modularisierung
 *                 1991 02 03: Revision
 *                 1991 05 27: Revision
 *                 1995-10-19: extracted from 1001
 *  latest update: 1998-08-16 12:33:38
 *  $Id: ned1018.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <time.h>
#include "ed.h"
#include "edhyx.h"

#ifndef USE_TK
#include <gg/maus.h>
#else
#define P1 STOP
#endif /* !USE_TK */

#include <gg/keys.h>
#include "proto.h"
extern struct WINDOWCTRL *aw;
static int block_mode;

#ifdef DEBUG
#include <stdio.h>
static char bu [80];
#endif /* DEBUG */

/* ------------------------------------------------------------------------ */
static int last_x= -2;
static int last_y= -2;
static int first_x= -2;
static int first_y= -2;

static time_t last_time= -1L;
static int last_dc_key= 0;
static int selection_active= 0;

/* pointer device button states */
#define BST_START       0
#define BST_B1          1
#define BST_B2          2
#define BST_B3          3
#define BST_WAIT      888
static int bst= BST_START;

/* ------------------------------------------------------------------------ */
int ned_mouse_event (int x, int y, int t, int abs_x, int abs_y)
{
  time_t act_time;
  int double_click= 0;          /* 1 -> double click event */
  int rv= 0;
  struct FEATURE **fp;

#ifdef MSDOS
  abs_x; abs_y; /* not used in MSDOS */
#endif /* MSDOS */

  switch (bst)
  {
    case BST_START:
      if (!t) break;

      act_time= time ((time_t *) 0);
      if (t == last_dc_key
          && (act_time == last_time || act_time-1 == last_time)
          && x == first_x
          && y == first_y
         )
      {
        double_click= 1;
      }

      last_time= act_time;
      last_dc_key= t;
      first_x= x;
      first_y= y;
      selection_active= 0;
      bst= t;

#ifdef DEBUG
      sprintf (bu, "be: [x=%d y=%d t=%d] (dc=%d)", x, y, t, double_click);
      ned_message_1 (bu);
#endif /* DEBUG */

      switch (t)
      {
        case 0x0001:
          switch (ned_mouse_set_cursor (x, y))
          {
            case 0: /* cursor in main text window */
              if (!double_click) break;
#ifndef USE_TK
              maus_disable ();
#endif /* !USE_TK */
              ned_eval_feature ();
              bst= BST_WAIT;
              break;

            case 1: /* cursor on window frame */
              break;

            case 2: /* cursor out of main text window */
              if (ned_search_button_bar (x, y, t)) bst= BST_WAIT;
              break;
          }

          rv= 1;
          break;

        case 0x0002:
#ifdef USE_TK
          /* TK: post a menu ... */
          ned_tk_special_event ((struct WINDOWCTRL *) 0, NED_TK_CMD_MOUSE_B2,
                                abs_x, abs_y);
#endif /* USE_TK */
          break;

        case 0x0004: /* middle button */
#ifdef __DONT_DO_THAT__ /* 1996-03-17 19:17:41 */
          switch (ned_mouse_set_cursor (x, y))
          {
            case 0: /* cursor in window */
#ifdef USE_TK
              if (!double_click) ned_tk_import_selection ();
#endif /* USE_TK */
              break;
          }
#endif /* __DONT_DO_THAT__ 1996-03-17 19:17:41 */

#ifdef USE_TK
          if (!double_click) ned_tk_import_selection ();
#endif /* USE_TK */
          rv= 1;
          break;
      }
      break;

    case BST_B1:
      if (t != 0x0001)
      {
        bst= t;
        break;
      }

      /* if (x == last_x && y == last_y) break; */

      rv= 1;
      if (!selection_active
          && (first_x != x || first_y != y)
          && x >= aw->ax && x <= aw->bx
          && y >= aw->ay && y <= aw->by
         )
      {
        block_mode= BLOCK_MODE_standard;
        ned_set_marker (aw, 0x7B); /* open brace */
        selection_active= 1;
#ifdef USE_TK
        ned_tk_block_export_flag (1);
#endif /* USE_TK */
        last_time= -1L;                   /* reset double click timer */
      }

      ned_mouse_set_cursor (x, y);

      /* EXP: 1996-05-27 10:25:40 */
      if ((fp= ned_feature_find3 (1)) != (struct FEATURE **) 0)
        show_feature (*fp);

      if (selection_active && (x != last_x || y != last_y)) p_blkend ();

#ifndef USE_TK
      maus_enable ();
#endif /* !USE_TK */
      break;

    case BST_B2: /* B2 still pressed */
      bst= t;
      break;

    case BST_WAIT:
      if (!t)
      {
        bst= BST_START;
#ifndef USE_TK
        maus_enable ();
#endif /* !USE_TK */
        rv= 1;
      }
      break;

    default:
      bst= t;
      break;
  }

#ifdef DEBUG
  sprintf (bu, "be: [x=%d y=%d t=%d]", x, y, t);
  ned_message_1 (bu);
#endif /* DEBUG */

  last_x= x;
  last_y= y;

  return rv;
}
