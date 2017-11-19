/*
 *  FILE %ned/07/ned0726.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *                 1991 07 10: Revision
 *  latest update: 1998-08-16 12:31:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_blk_duplicate (
register struct LINE  *s_start,
struct LINE  *s_stop,
struct LINE **d_start,
struct LINE **d_stop,
int sp1,
int sp2,
int copy_mode)
{
  register struct LINE **p;             /* Kopierte Zeile                   */
           struct LINE *p2;             /* Previous Line im copierten Block */
           struct LINE *p3;             /* temporary line pointer           */

  *d_start= *d_stop= p2= (struct LINE *) 0;
  if (s_start == (struct LINE *) 0 || s_stop == (struct LINE *) 0) return -1;

  p= d_start;
  for (; s_start != (struct LINE *) 0; s_start= s_start->next)
  {
#ifdef JUNK
    if (s_start == s_stop
        && copy_mode == BLOCK_MODE_standard
        && sp2 == 0) break;
#endif

    if (ned_copy_line (p, s_start) < 0) break;

    (*p)->prev= p2;
    if (p2 != (struct LINE *) 0) p2->next= *p;
    p2= *p;
    p= &p2->next;
    if (s_start == s_stop) break;
  }
  *d_stop= p2;

  /* splice begin and end of lines of block, if in standard block mode */
  if (copy_mode == BLOCK_MODE_standard)
  {
    int start_is_stop= 0;

    if (*d_stop == *d_start) start_is_stop= 1;
if (start_is_stop) ned_message_1 ("start is stop");

    if (sp2 >= 0 && ned_split2 (p3= *d_stop, &p2, sp2, 0) >= 0)
    {
      p3->next= p2->prev= (struct LINE *) 0;
      ned_lines_free (p2);
    }

    if (sp1 > 0 && ned_split2 (p3= *d_start, &p2, sp1, 0) >= 0)
    {
      *d_start= p2;
      p3->next= p2->prev= (struct LINE *) 0;
      ned_lines_free (p3);
    }
    if (start_is_stop) *d_stop= *d_start;
  }

  return 0;
}
