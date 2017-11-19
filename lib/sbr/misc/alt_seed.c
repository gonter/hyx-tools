/*
 *  FILE %sbr/alt_seed.c
 *
 *  written:       2000-08-28
 *  latest update: 2000-08-28 12:25:52
 *  $Id: alt_seed.c,v 1.3 2012/11/22 16:16:26 gonter Exp $
 *
 */

#include <stdlib.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
void alt_seed (void)
{
  long seed= (unsigned int) time ((long *) 0);
#ifndef MSDOS
  seed ^= getpid ();
#endif
  seed ^= (int) rand ();
  srand (seed);
}
