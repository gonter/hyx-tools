/*
 *  FILE %ds/ggcrypt/ggcryp09.c
 *
 *  generate a chex string for a given set of credentials and a challenge
 *
 *  written:       1995-05-02
 *  latest update: 1996-01-17 13:14:03
 *  $Id: ggcryp09.c,v 1.2 2003/06/25 10:12:50 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/ggcrypt.h>
#include <contrib/md5gg.h>

/* ------------------------------------------------------------------------ */
#define MAX_LINE 512
static char CHALLENGE_STRING [MAX_LINE];

/* ------------------------------------------------------------------------ */
char *agettok_get_challenge (
char *password_file,
char *user_from,
char *user_to,
char *resource_name,
char *challenge)
{
  char *afs_password;

  afs_password= agettok_get_resource_password (password_file,
                  user_from, user_to, resource_name, 0);

  if (afs_password == (char *) 0) return (char *) 0;

  sprintf (CHALLENGE_STRING, "%s:%s:%s:%s:%s", user_from, user_to,
           resource_name, challenge, afs_password);

  return MD5check_string ((unsigned char *) CHALLENGE_STRING);
}
