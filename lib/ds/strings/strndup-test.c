/*
 *  FILE %ds/strings/strndup-test.c
 *  Test module for strndup
 *  apparently, not all operating systems define strndup ()
 *  written: 2001-08-22
 *  $Id: strndup-test.c,v 1.1 2001/08/22 09:03:25 gonter Exp $
 */

#include <string.h>
#ifdef TEST_OK
#include <gg/strings.h>
#endif

int main (int argc, char *argv [])
{
  char *c;
  c= strndup ("urxn", 10);
  exit (0);
}


