/*
 *  FILE %sbr/ftrans07.c
 *
 *  Transfer some range of a file to another one.
 *
 *  written:       1994-10-31: cloned from ftransfer()
 *  latest update: 1996-10-12 12:09:33
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long ftransfer_crlf (FILE *fi, FILE *fo, long cpy_size)
{
  int ch;
  long fsiz= 0L;

  for (; cpy_size > 0L; cpy_size--)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    if (ch == '\n') fputc ('\r', fo);
    fputc (ch, fo);
    fsiz++;
  }

  return fsiz;
}
