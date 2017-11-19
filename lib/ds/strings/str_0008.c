/*
 *  FILE %ds/strings/str_0008.c
 *
 *  Anzahl der uebereinstimmenden Zeichen bestimmen
 *
 *  written:       1989 10 14: (aus STRINGS.SAR)
 *                 1992 09 13: revision
 *  latest update: 1996-11-03  9:15:19
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <gg/strings.h>

/* Anzahl der uebereinstimmenden Zeichen: --------------------------------- */
int match_lng (
char *s1,
char *s2,
int cnt)
{
  int c;
  int c1;
  int c2;

  if (s1 == (char *) 0 || s2 == (char *) 0 || s1 == s2) return 0;

  for (c= 0; ; c++)
    if (c == cnt || !(c1= *s1++) || !(c2= *s2++) || c1 != c2) return c;

  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef _DEBUG_MODULE_
struct TEST
{
  char *s1, *s2;
  int   lng;
} ;

# define TEST_CNT 7
struct TEST test [TEST_CNT] =
{
  "abcd", "abab", 4,
  "Gerhard", "Gonter", 99,
  "Gerhard", "Gerald", 99,

  "just the same", "just the same", 99,
  "this one", "this one is longer", 99,
  "this one is longer",  "this one", 99,
  "this one is longer",  "this one", 3
} ;

main ()
{
  int i, rc;

  for (i= 0; i < TEST_CNT; i++)
  {
    rc= match_lng (test[i].s1, test[i].s2, test[i].lng);
    printf ("s1='%s' s2='%s' lng=%d -> rc=%d\n",
            test[i].s1, test[i].s2, test[i].lng, rc);
  }  
}

#endif /* _DEBUG_MODULE */
