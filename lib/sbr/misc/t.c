/*
 *  FILE c:/usr/sbr/t.c
 *
 *  1991 06 24
 *
 */

# include <stdio.h>

static char line1 [100], line2 [100];

main ()
{
  int v1, v2, v3;

  for (;;)
  {
    printf ("1: "); scanf ("%[^\n]", line1); getchar ();
    printf ("2: "); scanf ("%[^\n]", line2); getchar ();
    v1 = strcmp        (line1, line2);
    v2 = strcmp_ebcdic (line1, line2);
    v3 = strcmp_c      (line1, line2);
    printf ("%d %d (ebcdic) %d (case)\n", v1, v2, v3);
  }
}
