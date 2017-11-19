/*
 *  FILE %sbr/dpp_0006.c
 *
 *  written:       1994-05-27
 *  latest update: 1996-11-26 20:58:01
 *  $Id: dpp_0006.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int ARG_long_eval (
const char *s,          /* Evaluierungsstring   */
int   o,                /* Offset               */
int   c,                /* Stellenzahl          */
int   b,                /* Basis                */
long *val)              /* Ergebnis in LONG     */
/* RETURN: 0 -> Fehler                          */
/*         1 -> OK                              */
{
  long v= 0;
  int i;
  int ch;

  for (i= 0; i <= o; i++) if (!s [i]) return 0;

  for (i = 0; i < c; i++)
  {
    if (!(ch= s [i+o])) break;
    if (ch >= '0' && ch <= '9')
      v= ((long) b)*v + ((long) (ch - '0')); else
    if (b > 10)
      if (ch >= 'a' && ch <= 'z')     /* !!!!!! */
        v= ((long) b)*v + ((long) (ch - 'a' + 10)); else
    if (ch >= 'A' && ch <= 'Z')
      v= ((long) b)*v + ((long) (ch - 'A' + 10));
  }

  *val= v;

  return 1;
}
