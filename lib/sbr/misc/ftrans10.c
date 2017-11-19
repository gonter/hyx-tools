/*
 *  FILE %sbr/ftrans10.c
 *
 *  Transfer some range of a file to another one.
 *
 *  written:       1996-10-12
 *  latest update: 1996-12-03 22:26:48
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long ftransfer_del_dot (FILE *fi, FILE *fo, long cpy_size)
{
  int ch;
  long fsiz= 0L;
  int status= 0;
  int dots= 0;

  for (; cpy_size > 0L; cpy_size--)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;

    switch (status)
    {
      case 0:                   /* begin of the line                        */
        if (ch == '.')
        {
          status= 1;
          dots= 1;
          continue;             /* don't issue that character               */
        }
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
          if (dots == 1)
          {
#ifdef TEST_NOT_NOW
1996-12-03 22:22:30 NOTE, Test
The complete line is the End-Of-Stream symbol.
            fputc ('\n', fo);
            fsiz++;
#endif /* TEST_NOT_NOW */
            goto DONE;
          }
          status= 0;
        }
        else if (ch == '.') dots++;
        else
        {
          fputc ('.', fo);
          fsiz++;
          status= 2;
        }
        break;

      case 2:                   /* any character                            */
        if (ch == '\n') status= 0;
        break;

      case 3:                   /* CR after lines with dots only            */
        if (ch == '\n')         /* CF LF on a line with dots only           */
        {
          if (dots == 1)
          {
#ifdef TEST_NOT_NOW
1996-12-03 22:26:05 see above...
            fputc ('\r', fo);
            fputc ('\n', fo);
            fsiz += 2;
#endif /* TEST_NOT_NOW */
            goto DONE;
          }
          fsiz++;
          fputc ('\r', fo);
          status= 0;
        }
        else                    /* something else, CR is spurious           */
        {
          fputc ('.', fo);
          fputc ('\r', fo);
          fsiz += 2;
          status= 2;
        }
        break;
    }

    fputc (ch, fo);
    fsiz++;
  }

DONE:
  return fsiz;
}
