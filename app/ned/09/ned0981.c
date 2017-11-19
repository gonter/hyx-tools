/*
 *  FILE %ned/09/ned0981.c
 *
 *  read various attributes
 *
 *  called by ned0903.c ned_read_setup (char *fn)
 *
 *  written:       1994-05-09
 *  latest update: 1997-10-26 10:48:29
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern int COL_BLOCK;

/* ------------------------------------------------------------------------ */
int stp_attr (FILE *fi, char *b, int max_b)
{
  int rc;
  char *w2;
  long p2;

  for (;;)
  {
    b[0]= 0;
    rc= fread_line (fi, b, max_b);
    if (rc <= 0 && feof (fi)) break;
    if (b[0] == '@') break;

    w2= locate_word (b, 1);
    p2= (w2 != (char *) 0) ? get_parameter_value (w2) : 0L;

    if (strncmp (b, "COL_BLOCK", 9) == 0) COL_BLOCK= (int) p2;
    if (strncmp (b, "CURSOR", 6) == 0) w_cursorsize (0x06, (int) p2);
  }
  return 0;
}
