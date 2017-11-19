/*
 *  FILE %ned/04/ned0429.c
 *
 *  write extraction information to file
 *
 *  written:       1992 04 05
 *  latest update: 1997-10-26 10:51:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/hytxt.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int q_extract (char *filename, char *message)
{
  FILE *fo;

  if ((fo= fopen (filename, "at")) == (FILE *) 0) return -1;

  fprintf (fo, "<extract appl=ned>\n");
  hyx_write_stamp (fo, (char *) 0);
  fprintf (fo, "msg %s\ncor %d %d %d\n",
           message, aw->znr, aw->cx+aw->hv-aw->ax, aw->hv);

  fprintf (fo, "</extract>\n");
  fclose (fo);

  return 0;
}
