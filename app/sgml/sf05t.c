/*
 *  FILE ~/usr/sgml/sf05t.c
 *
 *  Test modules sf03.c, sf04.c and sf05.c
 *
 *  written:       1994-08-06
 *  latest update: 1994-08-06
 *
 */

#include <stdio.h>
#include <gg/hytxt.h>

extern char *SFCHR_FRAME;

static char line1[100];
static char line2[100];
static char line3[100];

int testit (char *s)
{
    frame_name2url (s, line2, 100);
    url2frame_name (line2, line3, 100);
    printf ("original   : %s\n", s);
    printf ("URL        : %s\n", line2);
    printf ("frame again: %s\n", line3);
}

main ()
{
  testit (SFCHR_FRAME);
  for (;;)
  {
    printf ("frame name : ");
    scanf ("%[^\n]", line1);
    getchar ();
    testit (line1);
  }
  return 0;
}
