/*
 *  FILE ~/usr/lexicon/lex.c
 *
 *  latest update: 1995-07-16
 *
 */

#include <stdio.h>
#include <gg/lexicon.h>

int cdecl main (void);

/* ------------------------------------------------------------------------ */
int main ()
{
/**************
  printf ("enter lexicon path> ");
  scanf ("%s", line);
**************/

  LEXICON_init (0, "\\LEXICON\\");
  LEXICON_print (stdout);

  return 0;
}
