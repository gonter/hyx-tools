/*
 *  FILE %ds/strings/str_0053.c
 *
 *  prompt for a password and verify in a cycle
 *
 *  written:       1997-10-05
 *  latest update: 1999-11-28 12:26:17
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *get_password_verified (char *p1, char *p2)
{
  char *ver1;
  char *ver2;

  for (;;)
  {
    ver1= strdup_or_what (getpass (p1));
    ver2= strdup_or_what (getpass (p2));
    if (ver1 == (char *) 0 || ver2 == (char *) 0) return (char *) 0;

    if (strcmp (ver1, ver2) == 0) break;

    fprintf (stderr, "passwords don't match, try again!\n");
    free_or_what (ver1);
    free_or_what (ver2);
  }
  free_or_what (ver2);

  return ver1;
}
