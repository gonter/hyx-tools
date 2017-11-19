/*
 *  FILE %sgml/sf03.c
 *
 *  see also:
 *  sf04.c int cdecl url2frame_name (char *url, char *frame, int max_frame);
 *  sf05.c contains the translation tables SFCHR_FRAME and SFCHR_URL
 *
 *  written:       1994-04-12
 *  latest update: 1999-08-01 12:19:53
 *
 */

#include <stdio.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

extern char *SFCHR_FRAME;
extern char *SFCHR_URL;

/* ------------------------------------------------------------------------ */
int frame_name2url (char *frame, char *url, int max_url)
{
  int ch;
  int idx;

  if (max_url <= 2 || url == (char *) 0) return -1;

  for (; (ch= *frame++ & 0x00FF) != 0 && max_url > 2;)
  {
    if ((idx= chr_index (SFCHR_FRAME, ch)) >= 0)
    {
      *url++= '_';
      *url++= SFCHR_URL [idx];
      max_url -= 2;
    }
    else
    {
      *url++= (char) ch;
      max_url--;
    }
  }
  *url= 0;
  return 0;
}
