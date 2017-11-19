/*
 *  FILE %ned/00/ned0005.c
 *
 *  Datenstrukturen fuer EDITOR NED
 *  see Markers for the complete truth
 *
 *  written:       1987 09 09
 *  latest update: 1997-03-31 12:51:19
 *
 */

#include "ed.h"

/* ------------------------------------------------------------------------ */
struct MARKER b_first= { (struct WINDOWCTRL *) 0, (struct LINE *) 0, 0 };
struct MARKER b_last= { (struct WINDOWCTRL *) 0, (struct LINE *) 0, 0 };
struct MARKER b_beg= { (struct WINDOWCTRL *) 0, (struct LINE *) 0, 0 };
struct MARKER b_end= { (struct WINDOWCTRL *) 0, (struct LINE *) 0, 0 };

/* ------------------------------------------------------------------------ */
int blk= 0;                     /* 1 -> Block angezeigt                     */
int block_mode= BLOCK_MODE_standard;
                                /* 1 BLOCK_MODE_standard -> 'normaler' Modus*/
                                /* 2 BLOCK_MODE_line -> LINE Modus          */
                                /* 3 BLOCK_MODE_box -> Box Modus            */
