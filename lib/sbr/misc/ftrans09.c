/*
 *  FILE %sbr/ftrans09.c
 *
 *  Transfer some range of a file to another one.
 *  add a line with a single dot at the end of the file
 *
 *  see also: ftrans01.c : ftransfer (...)
 *
 *  written:       1996-10-10
 *  latest update: 1996-12-03 22:19:06
 *  $Id: ftrans09.c,v 1.2 2002/01/27 23:01:48 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long ftransfer_add_dot (FILE *fi, FILE *fo, long cpy_size)
{
  int ch= 0;                    /* character read from file                 */
  long fsiz= 0L;                /* bytes (without padded dots) transfered   */
  int status= 0;

  for (; cpy_size > 0L; cpy_size--)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;

    switch (status)
    {
      case 0:                   /* begin of the line                        */
        if (ch == '.') status= 1;
        else if (ch != '\n') status= 2;
        break;

      case 1:                   /* dots at the begin of the line            */
        if (ch == '\r')
        {
          status= 3;
          continue;             /* wait and see if there is a LF coming     */
        }
        else if (ch == '\n')
        {
          fputc ('.', fo);
          status= 0;
        }
        else if (ch != '.') status= 2;
        break;

      case 2:                   /* any character                            */
        if (ch == '\n') status= 0;
        break;

      case 3:                   /* CR after lines with dots only            */
        if (ch == '\n')         /* CF LF on a line with dots only           */
        {
          fputc ('.', fo);
          fputc ('\r', fo);
          fsiz++;
          status= 0;
        }
        else                    /* something else, CR is spurious           */
        {
          fputc ('\r', fo);
          status= 2;
        }
        break;
    }

    fputc (ch, fo);
    fsiz++;
  }

  if (ch != '\n')               /* the ending dot must be on a line of its  */
    fputc ('\n', fo);           /* own, otherwise it would not be           */
  fputs (".\n", fo);            /* recognized as the end of the stream!     */

  return fsiz;
}
