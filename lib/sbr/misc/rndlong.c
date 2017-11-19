/*
 *  FILE %sbr/rndlong.c
 *
 *  written:       1994-02-04
 *  latest update: 2000-08-28 12:25:49
 *  $Id: rndlong.c,v 1.3 2000/08/28 19:28:06 gonter Exp $
 *
 */

#include <stdlib.h>
#include <gg/dpp.h>

static int seed_done= 0;

/* ------------------------------------------------------------------------ */
long random_long ()
{
  long x;
  int rv;

  if (!seed_done)
  {
    seed_done= 1;
    alt_seed ();
    rv= rand () % 16;
    while (rv-- > 0) (void) rand ();
  }

  rv= rand () & 0x7FFF;
  x= ((long) rv) << 7;
  rv= rand () & 0x7FFF;
  x |= (long) rv;

  return x;
}
