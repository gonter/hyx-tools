/*
 *  FILE %ned/07/ned0702.c
 *
 *  set a marker
 *
 *  written:       1996-10-03
 *  latest update: 1997-06-28 22:35:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int key;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_set_marker_key ()
{
  ned_set_marker (aw, key);
}
