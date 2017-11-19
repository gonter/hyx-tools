/*
 *  FILE %ned/04/ned0427.c
 *
 *  File I/O: print a file
 *
 *  written:       1992 01 23
 *  latest update: 1997-10-26 10:52:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_pfile ()
{
  struct LINE *la;
  long la_offset, lz_offset;
  int f_write_mode= FLG2_none;

  for (la= aw->first;
       la != (struct LINE *) 0 && la->prev != (struct LINE *) 0;
       la= la->prev);

  if (aw->file_type == FTY_HYPER) f_write_mode= FLG2_format_change;

  ned_f_write (aw,
           "/dev/prn",
           (char *) 0,
           0,
           1,
           la,
           (struct LINE *) 0 /* Dummy */,
           &la_offset,
           &lz_offset,
           f_write_mode);

}
