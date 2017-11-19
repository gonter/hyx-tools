/*
 *  FILE ~/usr/contrib/md5/md5t1.c
 *
 *  written:       1994-07-17
 *  latest update: 1994-07-17
 *
 */

#include <stdio.h>
#include <contrib/md5gg.h>

int test_md5s (char *s)
{
  char *md5;
  md5= MD5check_string (s);
  printf ("%s \"%s\"\n", md5, s);
  return 0;
}

int main (void);

int main ()
{
  test_md5s ("1 2 3");
  test_md5s ("");
  test_md5s ("1 2 3");
  test_md5s ("1 2 3");
  test_md5s ("");

  test_md5s ("e");
  test_md5s ("b");

  return 0;
}

