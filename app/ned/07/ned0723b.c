/*
 *  FILE %ned/07/ned0723b.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1996-05-27
 *  latest update: 1997-08-28 18:31:13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;
extern int blk;
static int fresh_buffer= 1;

/* ------------------------------------------------------------------------ */
int ned_store_line_to_buffer (
int buffer_id,
struct LINE *lp_b,
struct LINE *lp_e,
int add_mode)
{
  struct NED_BUFFER *bu;

  ned_line_trigger_delete (lp_b, 1, 1);

/*** DEBUGGING T2D: sollte nichts mehr ausspucken! ***/
  ned_check_for_markers (lp_b, 1);
/*** DEBUGGING T2D ***/

  bu= ned_get_buffer (buffer_id, 1);

  if (add_mode == 0 || fresh_buffer)
  {
    ned_drop_buffer2 (bu);
EMPTY:
    bu->l_beg= lp_b;
    bu->l_end= lp_e;
    fresh_buffer= 0;
  }
  else
  { /* T2D: add a line to buffer */
    struct LINE *lb_e;

    if ((lb_e= bu->l_end) == (struct LINE *) 0
        || lp_b == (struct LINE *) 0
       ) goto EMPTY;

    lb_e->next= lp_b;
    lp_b->prev= lb_e;
    bu->l_end= lp_e;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_fresh_buffer ()
{
  return fresh_buffer= 1;
}
