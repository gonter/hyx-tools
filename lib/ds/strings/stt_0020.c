/*
 *  FILE %ds/strings/stt_0020.c
 *
 *  test split_string module
 *
 *  written:       1993-08-15
 *  latest update: 1996-02-25  0:25:06
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
static char *TESTS1 [] =
{
  "a:b:c",
  ":b:c",
  "a:b:",
  "a::c",
  "",
  ":::::",
  ":xx:",
  "xx",
  "abc::de:f:g::x",
  (char *) 0
} ;

/* ------------------------------------------------------------------------ */
static char *TESTS2 [] =
{
  "     ",
  " xx ",
  "xx",
  "abc  de f g  x",
  (char *) 0
} ;

/* ------------------------------------------------------------------------ */
#define N_SPLIT 40
static char *SPLIT [N_SPLIT];

static char tmp [1024];

/* ------------------------------------------------------------------------ */
int stt_0020 (char *str, int spl)
{
  int sc;
  int i;
  int n;

  strcpy (tmp, str);
  printf ("tmp=\"%s\"\n", tmp);
  printf ("spl='%c'\n", spl);

  sc= split_string (tmp, spl, SPLIT, N_SPLIT);
  n= (sc > N_SPLIT) ? N_SPLIT : sc;
  printf ("sc=%d  n=%d\n", sc, n);

  for (i= 0; i<n; i++)
    printf ("[%2d] %s\n", i, SPLIT[i]);

  printf ("--------------------------\n");

  return 0;
}

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  int i;
  char *s;

  argc; argv;

  for (i= 0; (s= TESTS1[i]) != (char *) 0; i++) stt_0020 (s, ':');
  for (i= 0; (s= TESTS2[i]) != (char *) 0; i++) stt_0020 (s, ' ');

  return 0;
}
