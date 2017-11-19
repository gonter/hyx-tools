/*
 *  FILE %ned/03/ned0312.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1991 01 29
 *  latest update: 2001-02-11 12:57:37
 *  $Id: ned0312.c,v 1.2 2001/02/12 00:03:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int get_confirmation (char *message, int std)
{
  int k;

  ned_message_1 (message);

RETRY:
  k= test_maus ('Y', 'N', 0);
  if (k == 0x1B) return -1;
  if (k == 'j' || k == 'J' || k == 0x09 ||
      k == 'y' || k == 'Y' || k == 0x19) return 1;

  if (k == 'n' || k == 'N' || k == 0x0E) return 0;

  if (std == -1)
  {
    vi_bell ();
    goto RETRY;
  }

  return std;
}
