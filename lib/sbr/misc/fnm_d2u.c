/*
 *  FILE ~/usr/sbr/fnm_d2u.c
 *
 *  translate a filename from dos to unix
 *
 *  written:       1994-12-31
 *  latest update: 1995-06-11
 *
 */

#include <gg/strings.h>
#include <gg/filename.h>
 
/* ------------------------------------------------------------------------ */
int filename_dos2unix (char *d, char *s)
{
  int ch;

  for (;; s++)
  {
    switch (ch= (*s & 0x00FF))
    {
      case '(':         /* quote offending characters */
      case ')':
        *d++ = '\'';
        *d++ = (char) ch;;
        *d++ = '\'';
        break;
      case '\\':
        *d++ = '/';
        break;
      case ':':
        *d++ = '.';
        *d++ = 'd';
        *d++ = 'r';
        *d++ = 'i';
        *d++ = 'v';
        *d++ = 'e';
        *d++ = '/';
        break;
      default:
        *d++= (char) lower_case (ch);
        break;
    }
    if (*s == 0) break;
  }

  return 0;
}
