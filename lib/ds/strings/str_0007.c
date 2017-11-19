/*
 *  FILE ~/usr/sbr/str_0007.c
 *
 *  generate checkstrings over strings.
 *
 *  written:       1989 10 14: (from STRINGS.SAR)
 *  latest update: 1995-05-13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int string_hash (
char *str,                      /* string to check                          */
int lng,                        /* length of the string to check            */
char *hash,                     /* hash string generated                    */
int hlng)                       /* length of wanted hash-strings            */
{
  int i;

  for (i=0; i<hlng; i++) hash [i       ]  = 0;
  for (i=0; i< lng; i++) hash [i % hlng] += str [i];

  return 0;
}
