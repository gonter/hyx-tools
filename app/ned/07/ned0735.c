/*
 *  FILE %ned/07/ned0735.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *  latest update: 1997-06-28 22:48:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct MARKER b_end;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_jmp_blkend ()
{
  ned_set_marker (aw, '\'');
  q_jmp_marker (&b_end); 
}
