/*
 *  FILE %ned/07/ned0725.c
 *
 *  insert a block in line mode
 *
 *  written:       1987 04 08
 *  latest update: 1997-06-29 14:05:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_blk_insert (            /* Block einfaedeln                         */
struct LINE *wh,                /* Einfuegeposition in Zeilenliste          */
struct LINE *start,             /* Begin des einzufuegenden Blocks          */
struct LINE *stop)              /* Ende des einzufuegenden Blocks           */
{
  if (wh == (struct LINE *) 0
      || start == (struct LINE *) 0
      || stop  == (struct LINE *) 0
     ) return -1;

  start->prev= wh;
  if ((stop->next= wh->next) != (struct LINE *) 0) wh->next->prev= stop;
  wh->next= start;

  return 0;
}
