/*
 *  FILE %ned/07/ned0763.c
 *
 *  paste the name of the last renamed object (file or frame)
 *
 *  written:       1996-03-17
 *  latest update: 1996-11-03 17:05:34
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern char *ned_renamed_object;
extern int block_mode;

/* ------------------------------------------------------------------------ */
int ned_paste_renamed_object ()
{
  int rc;

  block_mode= BLOCK_MODE_standard;
  p_blkbeg ();
  rc= ned_paste_string (ned_renamed_object, 0, (char *) 0, (char *) 0);
  p_blkend ();

  return rc;
}
