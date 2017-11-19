/*
 *  FILE %ds/strings/str_0203.c
 *
 *  Verify if a string only contains characters from a reference set.
 *  (see REXX)
 *
 *  Returns position of first character that is *NOT* contained
 *  in the reference set.  A return value of 0 indicates that
 *  all characters are contained in the reference set.
 *  The position is given (as in REXX) in the interval 1..N,
 *  where N is the length of the string.
 *
 *  written:       1993-01-20
 *  latest update: 1995-05-29
 *  $Id: str_0203.c,v 1.2 2004/05/25 22:07:18 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int verify (char *string, char *reference)
{
  int j;
  int i= 0;             /* index of examined character */
  int ch;               /* examined character   */
  int rch;              /* reference character  */
  int found;

  while ((ch= *string++) != 0)
  {
    i++;
    found= 0;
    for (j= 0; (rch= reference [j]) != 0; j++)
      if (ch == rch)
      {
        found= 1;
        break;
      }
    if (!found) return i;
  }

  return 0;
}
