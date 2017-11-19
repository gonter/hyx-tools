/*
 *  FILE C:\usr\sbr\strings.arc [stt_0008.c]
 *
 *  1990 06 02
 *
 */

# include "strings.h"

struct TEST
{
  char *s1, *s2;
  int   lng;
} ;

/* ------------------------------------------------------------------------ */
# define TEST1_CNT 7
struct TEST test1 [TEST1_CNT] =
{
  "abcd", "abab", 4,
  "Gerhard", "Gonter", 99,
  "Gerhard", "Gerald", 99,

  "just the same", "just the same", 99,
  "this one", "this one is longer", 99,
  "this one is longer",  "this one", 99,
  "this one is longer",  "this one", 3  
} ;

xxtest1 ()
{
  int i, rc;

  for (i=0; i<TEST1_CNT; i++)
  {
    rc = match_lng (test1[i].s1, test1[i].s2, test1[i].lng);
    printf ("s1='%s' s2='%s' lng=%d -> rc=%d\n",
            test1[i].s1, test1[i].s2, test1[i].lng, rc);
  }  
}

/* ------------------------------------------------------------------------ */
# define TEST2a_CNT 6
char *test2a [TEST2a_CNT] =
{
  "Re:xx", "Re: xx", "re:  XX", "RE:    ",
  "xx yz", "abc Re: aa"
};

# define TEST2b_CNT 3
struct TEST test2b [TEST2b_CNT] =
{
  "Subject: Designing online documents",
  "Subject: re: Designing online documents",
  0,
  "Subject: Designing online documents",
  "Subject: re: Designing documents",
  0,
  "Subject: Designing online documents",
  "Subject: Designing online documents",
  0
} ;

xxtest2 ()
{
  int i, rc;

  printf ("\nTEST2a: rc=skip_re (s)\n");
  for (i=0; i<TEST2a_CNT; i++)
  {
    rc = skip_re (test2a[i]);
    printf ("s='%s' -> rc=%d\n", test2a[i], rc);
  }  

  printf ("\nTEST2b: rc=strcmp_cre (s1, s2)\n");
  for (i=0; i<TEST2b_CNT; i++)
  {
    rc = strcmp_cre (test2b[i].s1, test2b[i].s2);
    printf ("s1='%s' s2='%s' -> rc=%d\n",
            test2b[i].s1, test2b[i].s2, rc);
  }  
}

/* ------------------------------------------------------------------------ */
# define TEST3_CNT 4
struct TEST test3 [TEST3_CNT] =
{
  "xyz", "abc", 0,
  "*", "xyz", 0,
  "*abcd*", "xyabxy", 0,
  "*abcd*", "xxababcdyy", 0
} ;

main ()
{
  int i, rc;

  printf ("\nTEST3: rc=match (pat, cmp)\n");
  for (i=0; i<TEST3_CNT; i++)
  {
    rc = match (test3[i].s1, test3[i].s2);
    printf ("pat='%s' cmp='%s' rc=%d\n",
            test3[i].s1, test3[i].s2, rc);
  }  
}

