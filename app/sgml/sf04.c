/*
 *  FILE %sgml/sf04.c
 *
 *  see also:
 *  sf03.c int cdecl frame_name2url (char *frame, char *url, int max_url);
 *  sf05.c contains the translation tables SFCHR_FRAME and SFCHR_URL
 *
 *  written:       1994-04-12
 *  latest update: 1999-08-01 12:17:36
 *
 */

#include <stdio.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

extern char *SFCHR_FRAME;
extern char *SFCHR_URL;

/* ------------------------------------------------------------------------ */
int url2frame_name (char *url, char *frame, int max_frame)
{
  int ch;
  int ch_val= 0;
  int st= 0;
  int idx;

  if (max_frame < 2 || frame == (char *) 0) return -1;

  for (; (ch= *url++ & 0x00FF) != 0 && max_frame > 1;)
  {
    switch (st)
    {
      case 0:
        if (ch == '_') st= 1;
        else
        if (ch == '%')
        {
          st= 3;
          ch_val= 0;
        }
        else
        {
          *frame++= (char) ch;
          max_frame--;
        }
        break;

      case 1:
        if ((idx= chr_index (SFCHR_URL, ch)) >= 0)
        {
          *frame++= SFCHR_FRAME [idx];
        }
        else
        {
          *frame++= (char) ch;
        }
        max_frame--;
        st= 0;
        break;

      case 3:
      case 4:
        if (ch >= '0' && ch <= '9')
        {
          ch_val= ch_val*16 + ch - '0';
        }
        else
        if (ch >= 'a' && ch <= 'f')
        {
          ch_val= ch_val*16 + ch - 'a' + 10;
        }
        else
        if (ch >= 'A' && ch <= 'F')
        {
          ch_val= ch_val*16 + ch - 'A' + 10;
        }
        if (st == 3)
        {
          st= 4;
        }
        else
        {
          st= 0;
          *frame++= (char) ch_val;
        }
        break;
    }
  }
  *frame= 0;

  return 0;
}
