/*
 *  FILE ~/usr/sbr/dpp_0004.c
 *
 *  written:       1990 01 20: aus NED00.C ausgelagert
 *                 1991 01 29: Revision
 *                 1994-05-27: was: ned0317.c
 *  latest update: 1994-11-13
 *  $Id: dpp_0004.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int ARGDeval (
const char *s,               /* Evaluierungsstring */
int   o,                     /* Offset             */
int   c,                     /* Stellenzahl        */
int   b,                     /* Basis              */
int   d)                     /* Defaultwert <<<<<< */
{
  int i;

  for (i= 0; i <= o; i++) if (!s [i]) return d;

  return ARGeval (s, o, c, b);
}
