/*
 *  FILE %ned/09/ned0911.c
 *
 *  translate a key sequence into its binary representation
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *  latest update: 1997-10-26 11:13:45
 *  $Id: ned0911.c,v 1.2 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dpp.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int trans_str (
const char *si,                 /* string input                             */
char *so,                       /* output string                            */
int size)                       /* maximum size in the destination buffer   */
/* return: number o bytes in the destination buffer                         */
{
  int i= 0;
  int o= 0;
  int j;

  for (; size > 0; size--)
  {
    switch (si [i])
    {
      case '^':
        if (!(j= si [++i]))
        {
          so [o]= 0;
          return o;
        }
        if (j >= 'a' && j <= 'z') j = j - 'a' + 1; else
        if (j >= 'A' && j <= 'Z') j = j - 'A' + 1;
        else break;
        so [o++]= (char) j;
        i++;
        break;

      case '\\':
        switch (j=si [++i])
        {
          case '\\': so [o++]= '\\'; break;
          case 'e' : so [o++]= 0x1B; break;
          case 'n' : so [o++]= '\n'; break;
          case '^' : so [o++]=  '^'; break;
          case '-' : so [o++]=  ' '; break;
          case '#' : so [o++]=  '#'; break;
          case 'x' : case 'X':
            if (! si [++i])
            {
              so [o]= 0;
              return o;
            }
            so [o++]= (char) ARGeval (si, i, 2, 16);
            for (j= 0; j < 2; j++)
              if (! si [++i])
              {
                so [--o]= 0;
                return o-1;
              }
            i--;
            break;
          case '0' : case '1': case '2': case '3':
          case '4' : case '5': case '6': case '7':
            so [o++]= (char) ARGeval (si, i, 3, 8);
            for (j= 0; j < 3; j++)
            if (! si [++i])
            {
              so [--o]= 0;
              return o-1;
            }
            i--;
            break;
        }
        i++;
        break;

      default:
        if (!(so [o++]= si [i++])) return o-1;
    }
  }

  return o;
}
