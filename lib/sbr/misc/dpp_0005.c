/*
 *  FILE %sbr/dpp_0005.c
 *
 *  written:       1990 01 20: aus NED00.C ausgelagert
 *                 1991 01 29: Revision
 *  latest update: 1996-01-31 22:11:11
 *  $Id: dpp_0005.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int ARGeval (
const char *s,               /* Evaluierungsstring */
int   o,                     /* Offset             */
int   c,                     /* Stellenzahl        */
int   b)                     /* Basis              */
{
  int v = 0, i, ch;

  for (i = 0; i < c; i++)
  {
    if (!(ch = s [i+o])) break;
    if (ch >= '0' && ch <= '9')
      v= b*v + ch - '0';
    else
    if (b > 10)
    {
      if (ch >= 'a' && ch <= 'z')     /* !!!!!! */
        v = b*v + ch - 'a' + 10;
      else
      if (ch >= 'A' && ch <= 'Z')
        v = b*v + ch - 'A' + 10;
    }
  }

  return v;
}
