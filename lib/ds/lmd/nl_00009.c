/*
 *  FILE /usr/nl_kr/lib/nl_00009.c
 *
 *  1990 01 28
 *
 */

# include <stdio.h>
# inlcude <gg/lookup.h>

static char LUT [4000];

static int LUT_IDX =0;


/* ------------------------------------------------------------------------ */
lookup_insert (char *w)
{
  int i;

  if (LUT_IDX == 0)
  {
    strcpy (LUT, w);
    LUT_IDX = strlen (w)+1;
    printf ("First Word %s\n", w);
    return 0;
  }

  for (i=0;

  return 0;
}

/* ------------------------------------------------------------------------ */
main ()
{
  char line [400];

  for (;;)
  {
    printf ("Wort: "); scanf ("%s", line);
    lookup_insert (line);
  }
}



