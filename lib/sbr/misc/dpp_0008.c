/*
 *  FILE %sbr/dpp_0008.c
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
long msdos_get_long (char *s)
{
  int v1, v2, v3, v4;

  v1= *s++ & 0x00FF;
  v2= *s++ & 0x00FF;
  v3= *s++ & 0x00FF;
  v4= *s   & 0x00FF;

  return ((v4*256 + v3)*256 + v2)*256 + v1;
}
