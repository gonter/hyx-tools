/*
 *  FILE %ds/ytree/yt_00015.c
 *
 *  write out lut file
 *
 *  written:       1995-01-07
 *  latest update: 1996-01-21 23:37:30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_dump_to_lut_file (char *name_lut, struct YTREE *yt)
{
  FILE *lut;

  /* write lut file back */
  if ((lut= fopen (name_lut, "wb")) == (FILE *) 0) return -1;
  ytree_size (yt);
  ytree_dump (lut, yt);
  fclose (lut);

  return 0;
}
