/*
 *  FILE %ds/mime/mime0001.c
 *
 *  mime operations
 *
 *  written:       2001-12-24
 *  latest update: 2001-12-24 12:43:19
 *  $Id: mime0003.c,v 1.2 2002/01/02 09:10:25 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/mail.h>

/* ------------------------------------------------------------------------ */
int mime_convert_xurl (char *line, char *line2, int MAX_LINE, int escape)
{
  int ch;
  int cnt= 0;
  int sixel_v1= 0;
  int sixel_v2= 0;
  int mime_mode= MIME_url_encoded;

  if (line == (char *) 0 || line2 == (char *) 0 || MAX_LINE <= 0) return -1;

  for (;;)
  {
    ch= *line++ & 0x00FF;
    if (ch == 0x00 || MAX_LINE <= 3)
    {
      *line2= 0;
      break;   /* these are URLs */
    }

    if (ch >= 0x007F || ch <= 0x20 || ch == escape)
    {
      sprintf (line2, "%c%02X", escape, ch);
      cnt += 3;
      MAX_LINE -= 3;
      line2 += 3;
    }
    else
    {
      *line2++= (char) ch;
      MAX_LINE--;
      cnt++;
    }
  }

  return cnt;
}
