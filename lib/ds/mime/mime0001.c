/*
 *  FILE %ds/mime/mime0001.c
 *
 *  mime operations
 *
 *  written:       1996-02-23
 *  latest update: 1996-08-15 12:14:15
 *  $Id: mime0001.c,v 1.2 2001/12/24 16:21:12 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/mail.h>

extern char sixel_table [];

/* ------------------------------------------------------------------------ */
int mime_convert_line (char *line, char *line2, int MAX_LINE, int mime_mode)
{
  int ch;
  int cnt= 0;
  int b64_phase= 0;
  int sixel_v1= 0;
  int sixel_v2= 0;

  if (line == (char *) 0 || line2 == (char *) 0 || MAX_LINE <= 0) return -1;

  for (;;)
  {
    ch= *line++ & 0x00FF;
    if (MAX_LINE <= 3)
    {
      *line2= 0;
      goto DONE;
    }

    if (ch >= 0x007F)
    {
      switch (mime_mode)
      {
        case MIME_quoted_printable:
          sprintf (line2, "=%02X", ch);
          cnt += 3;
          MAX_LINE -= 3;
          line2 += 3;
          break;

        case MIME_base64:
          switch (b64_phase)
          {
            case 0:
              sixel_v1= (ch >> 2) & 0x3F;
              sixel_v2= (ch & 0x03) << 4;

              *line2++= sixel_table [sixel_v1];
              MAX_LINE--;
              cnt++;
              b64_phase++;
              break;

            case 1:
              sixel_v1= (ch >> 4) & 0x0F;
              sixel_v1 |= sixel_v2;
              sixel_v2= (ch & 0x0F) << 2;

              *line2++= sixel_table [sixel_v1];
              MAX_LINE--;
              cnt++;
              b64_phase++;
              break;

            case 2:
              sixel_v1= (ch >> 6) & 0x03;
              sixel_v1 |= sixel_v2;
              sixel_v2= (ch & 0x3F);

              *line2++= sixel_table [sixel_v1];
              *line2++= sixel_table [sixel_v2];
              MAX_LINE -= 2;
              cnt += 2;
              b64_phase= 0;
              break;
          }
          break;

        default:
          goto NOPE;
      }
    }
    else
    {
NOPE:
      *line2++= (char) ch;
      MAX_LINE--;
      cnt++;
    }

    if (ch == 0x00) break;
  }

  switch (mime_mode)
  {
    case MIME_base64:
      for (; b64_phase > 0; b64_phase--)
      {
        *line2++= '=';
        cnt++;
      }
      break;
  }

DONE:
  return cnt;
}
