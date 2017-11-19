/*
 *  FILE %sbr/ftrans06.c
 *
 *  Transfer some range of a file to another one but only
 *  up to a line feed.
 *
 *  written:       1994-07-31
 *  latest update: 1995-10-20
 *  $Id: ftrans06.c,v 1.2 2001/12/19 08:07:49 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long ftransfer_line (FILE *fi, FILE *fo, long cpy_size)
{
  int ch;
  long fsiz= 0L;

  for (; cpy_size > 0L; cpy_size--)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    fputc (ch, fo);
    fsiz++;
    if (ch == '\n') break;
  }

  return fsiz;
}
