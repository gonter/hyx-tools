/*
 *  FILE ~/usr/sbr/str_0202.c
 *
 *  translate (see REXX)
 *
 *  written:       1993-01-15
 *  latest update: 1994-08-13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *translate (char *s, char *tbl_in, char *tbl_out)
{
  int j;
  int l_s;
  int l_in;
  int l_out;

  if (s == (char *) 0) return (char *) 0;
  if (tbl_in == (char *) 0 || tbl_out == (char *) 0) return s;

  l_s= strlen(s);
  l_in= strlen (tbl_in);
  l_out= strlen (tbl_out);
  if (l_in > l_out) l_in= l_out;

  for (j= 0; j<l_in; j++) xchange (s, tbl_in [j], tbl_out [j]);

  return s;
}
