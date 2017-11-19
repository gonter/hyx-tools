/*
 *  FILE %ned/10/ned1010.c
 *
 *  Maus Steuerung
 *
 *  written:       1988 09 04
 *                 1990 01 20: Modularisierung
 *                 1991 02 03: Revision
 *                 1991 05 27: Revision
 *  latest update: 1997-10-26 10:22:18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/keys.h>
#ifdef USE_MOUSE
#include <gg/maus.h>
#endif
#include "proto.h"

extern int maus_angeschlossen;
extern ned_input_handler *nextchar;
extern int MPflag;
extern int jou_flag;

/* ------------------------------------------------------------------------ */
int test_maus (int left, int right, int left_right)
{
#ifdef USE_MOUSE
  int x, y, t;
  int rc= 0;

  if (! maus_angeschlossen) return (*nextchar) ();

  maus_enable ();
  for (;;)
  {
    if (kbhit () || jou_flag == 2 || MPflag)
    {
      maus_disable ();
      return (*nextchar) ();
    }

    maus_position (&x, &y, &t);

    switch (t & 0x07)
    {
      case 0x01:
        rc= left;
        goto STOP;
      case 0x02:
        rc= right;
        goto STOP;
      case 0x03:
        rc= left_right;
        goto STOP;
      default:
        break;
    }
  }

STOP:

  do
  {
    maus_position (&x, &y, &t);
  } while (t != 0);

  return rc;

#else

#ifdef MSDOS
  left; right; left_right;
#endif

  return (*nextchar) ();
#endif
}
