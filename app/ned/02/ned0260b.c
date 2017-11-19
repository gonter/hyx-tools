/*
 *  FILE %ned/02/ned0260b.c
 *
 *  vi emulation: jump to a marker
 *
 *  written:       1996-05-27
 *  latest update: 1997-05-30 17:51:26
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int ned_jmp_marker (int marker_id, int flg)
{
  struct MARKER *mrk;

  if ((mrk= ned_get_marker (marker_id, 0)) == (struct MARKER *) 0) return -1;

  q_jmp_marker (mrk);
  if (flg & 0x0001) vi_jmp_boln ();
  if (flg & 0x0002) ned_jmp_boln ();

  return 0;
}
