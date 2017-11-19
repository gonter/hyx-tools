/*
 *  FILE %ds/strings/str_0046.c
 *
 *  written:       1995-12-08
 *  latest update: 1995-12-08
 *  $Id: str_0046.c,v 1.3 2005/02/19 03:37:02 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int sgml_encode (char *str, char *tmp, int str_size)
{
  int ch;
  char *dst;
  char *src;
  int rv= 0;

  if (str == (char *) 0 || tmp == (char *) 0 || str_size < 0) return -1;

  dst= tmp;
  src= str;

  while (str_size > 0)
  {
    switch (ch= (*src++ & 0x00FF))
    {
      case '&':
        if (str_size <= 5) goto TOO_SHORT;
        strcpy (dst, "&amp;");
        dst += 5;
        str_size -= 5;
        break;

      case '<':
      case '>':
        if (str_size <= 4)
        {
TOO_SHORT:
          ch= 0;
          rv= 1;
          break;
        }
        strcpy (dst, (ch == '<') ? "&lt;" : "&gt;");
        dst += 4;
        str_size -= 4;
        break;

      default:
        *dst++= (char) ch;
        str_size--;
        break;
    }
    if (ch == 0) break;
  }

  strcpy (str, tmp);

  return rv;
}
