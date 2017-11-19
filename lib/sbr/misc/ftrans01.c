/*
 *  FILE %sbr/ftrans01.c
 *
 *  Transfer some range of a file to another one.
 *
 *  see also: ftrans09.c : ftransfer_add_dot (...)
 *
 *  written:       1990-09-20
 *  latest update: 1995-12-10
 *  $Id: ftrans01.c,v 1.2 2002/01/27 23:01:48 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long ftransfer (FILE *fi, FILE *fo, long cpy_size)
{
  int ch;
  long fsiz= 0L;

  for (; cpy_size > 0L; cpy_size--)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    fputc (ch, fo);
    fsiz++;
  }

  return fsiz;
}
