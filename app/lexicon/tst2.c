/*
 *  FILE ~/usr/lexicon/tst2.c
 *
 *  Testmodul fuer parse0019.c
 *
 *  written:       1991 04 28
 *  latest update: 1995-07-16
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
static char line [256];
static char lin2 [256];
static char *pts [ 64];
static int   ptt [ 64];

static char *str_types [] = { "???", "TAG", "PAR", "ANM", "AVL" } ;

int cdecl main (void);


/* ------------------------------------------------------------------------ */
int main ()
{
  int parsed_items;
  int i;

  for (;;)
  {
    printf ("tag sequence>");
    scanf ("%[^\n]", line);
    if (feof (stdin)) break;
    fgetc (stdin);
    parsed_items= parse_tag_sequence (line, lin2, pts, ptt, 64);
    printf ("parsed_items=%d\n", parsed_items);
    for (i=0; i <parsed_items; i++)
    {
      printf ("item[%d] (%s) = '%s'\n",
              i, str_types [ptt[i]], pts[i]);
    }
  }

  return 0;
}
