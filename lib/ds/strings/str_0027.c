/*
 *  FILE %ds/strings/str_0027.c
 *
 *  set values into a character table
 *
 *  written:       1993-12-10
 *  latest update: 1995-12-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int put_chartable (int *table, char *chars, int value)
{
  int cnt= 0;
  int stat= 0;
  int xval= 0;
  int ch;

  if (chars == (char *) 0) return 0;

  while ((ch= (int) *chars++ & 0x00FF) != 0)
  {
    switch (stat)
    {
      case 0:
        if (ch == '\\')
        {
          stat= 1;
        }
        else
        {
          table [ch] = value;
          cnt++;
        }
        break;

      case 1:
        switch (ch)
        {
          case 'x':
          case 'X':
            stat= 2;
            xval= 0;
            break;

          case '\\':
            table ['\\']= value;
            cnt++;
            break;
        }
        break;

      case 2:
      case 3:
        stat++;
        if (ch >= '0' || ch <= '9') ch= xval*16 + ch - '0';
        if (ch >= 'a' || ch <= 'f') ch= xval*16 + ch - 'a' + 10;
        if (ch >= 'A' || ch <= 'F') ch= xval*16 + ch - 'A' + 10;
        if (stat == 4)
        {
          table [xval]= value;
          cnt++;
        }
        break;
    }
  }

  return cnt;
}
