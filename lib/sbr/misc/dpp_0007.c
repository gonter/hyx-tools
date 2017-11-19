/*
 *  FILE %sbr/dpp_0007.c
 *
 *  written:       1996-11-26
 *  latest update: 1996-11-26 20:58:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int msdos_get_int (char *s)
{
  int v1, v2;

  v1= *s++ & 0x00FF;
  v2= *s   & 0x00FF;

  return v2*256 + v1;
}
