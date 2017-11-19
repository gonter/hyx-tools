/*
 *  FILE ~/usr/sbr/str_0109.c
 *
 *  written:       1989 10 14: (aus STRINGS.SAR)
 *                 1992 03 13: revision
 *  latest update: 1994-08-01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
void delstr (           /* Loesche ein Zeichen          */
char *s,                /* aus diesem String            */
int p)                  /* ab dieser Position           */
                        /* und verschiebe den Rest      */
{
  for (; s [p]; p++)
    s [p]= s [p+1];
}
