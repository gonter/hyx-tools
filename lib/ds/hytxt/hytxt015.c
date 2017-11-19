/*
 *  FILE %ds/hytxt/hytxt015.c
 *
 *  written:       1993-01-21
 *  latest update: 1996-12-22 21:05:42
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int sgml_write_data (
FILE *fo,
char *open_tag,
char *close_tag,
char *buffer,
int buffer_size)
{
  int ch;
  int outc= 0;

/**************************************
  if (open_tag == (char *) 0) && close_tag == (char *) 0)
    return fwrite (buffer, 1, buffer_size, fo);
**************************************/

  if (open_tag != (char *) 0)
    outc += fwrite (open_tag, 1, strlen (open_tag), fo);

  while (buffer_size-- > 0)
  {
    ch= *buffer++ & 0x00FF;
    switch (ch)
    {
      case '<': outc += fputs ("&lt;", fo); break;
      case '>': outc += fputs ("&gt;", fo); break;
      case '&': outc += fputs ("&amp;", fo); break;
      case 0:   outc += fputs ("&null;", fo); break;
      default:
        fputc (ch, fo);
        outc++;
        break;
    }
  }

  if (close_tag != (char *) 0)
    outc += fwrite (close_tag, 1, strlen (close_tag), fo);

  return outc;
}
