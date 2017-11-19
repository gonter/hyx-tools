/*
 *  FILE ~/usr/sbr/ggcryp10.c
 *
 *  AFS shortcut authentication
 *
 *  written:       1995-05-10
 *  latest update: 1995-05-10
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/ggcrypt.h>

static char *default_sca_directory= "/usr/spool/sca/";

/* ------------------------------------------------------------------------ */
char *sca_get_sigfile (char *username)
{
  char *m;
  int l1;
  int l;

  if (username == (char *) 0 || *username == 0) return (char *) 0;

  l= (l1= strlen (default_sca_directory)) + strlen (username) + 2;
  if ((m= (char *) malloc (l)) != (char *) 0)
  {
    strcpy (m, default_sca_directory);
    strcpy (m+l1, username);
  }

  return m;
}
