/*
 *  FILE %ned/07/ned0725b.c
 *
 *  insert a block into a line, taking block mode into consideration
 *  returns a pointer to the last line
 *
 *  written:       1995-03-22
 *  latest update: 1997-06-29 14:26:19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;

/* ------------------------------------------------------------------------ */
int ned_blk_insert2 (           /* Block einfaedeln                         */
struct LINE *act_line,          /* Einfuegeposition in Zeilenliste          */
int xcx,                        /* Einfuegeposition innerhalb der Zeile     */
struct LINE *la,                /* Begin des einzufuegenden Blocks          */
struct LINE *lb)                /* Ende des einzufuegenden Blocks           */
{
  struct LINE *line_splitted;
  struct LINE *rv= (struct LINE *) 0;
  int offset;

  switch (block_mode)
  {
    case BLOCK_MODE_box:
    case BLOCK_MODE_line:
      ned_blk_insert (act_line, la, lb);
      rv= lb;
      offset= lb->lng;
      break;

    case BLOCK_MODE_standard:
      if (ned_split2 (act_line, &line_splitted, xcx, 0) >= 0)
      {
        if (la == lb)
        {
          rv= act_line;
          offset= xcx + la->lng;
        }
        else
        {
          rv= lb;
          offset= lb->lng;
        }

        ned_join2 (lb, line_splitted);
        ned_join2 (act_line, la);
      }
      break;
  }

  ned_set_marker2 ((struct WINDOWCTRL *) 0, rv, offset, 
                   ned_get_marker (NED_TMARK_INSERT2, 1));

  return 0;
}
