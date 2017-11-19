/*
 *  FILE %ds/strings/str_0047.c
 *
 *  read string from file
 *
 *  written:       1990 07 29
 *  latest update: 1995-12-25
 *  $Id: str_0047.c,v 1.3 2009/10/13 13:00:07 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
char *read_string (FILE *fi, int string_length)
{
  char *str= (char *) 0;

  if (string_length > 0
      && (str= malloc (string_length+1)) != (char *) 0
     )
  {
    fread (str, string_length, 1, fi);
    str [string_length]= 0;
  }

  return str;
}
