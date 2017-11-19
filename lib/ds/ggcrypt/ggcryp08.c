/*
 *  FILE %ds/ggcrypt/ggcryp08.c
 *
 *  written:       1995-05-02
 *  latest update: 1997-01-25 14:53:11
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/sbr.h>
#include <gg/dpp.h>
#include <gg/strings.h>
#include <gg/ggcrypt.h>
#include <contrib/md5gg.h>

/* #define DEBUG */

/* ------------------------------------------------------------------------ */
#define AGETTOK_HASH_SIZE 4             /* number of bytes used for hash    */
#define MAX_BUFFER 40                   /* 32 Byte max minus 4 at most      */
#define MAX_LINE 256                    /* a bit more space for other stuff */

static char AGETTOK_HASH  [MAX_BUFFER]; /* lookup hash string               */
static char AGETTOK_KEY   [MAX_BUFFER]; /* encryption key                   */
static char pAGETTOK_HASH [MAX_BUFFER]; /* printable hash string            */

static char AGETTOK_PASS  [MAX_LINE];   /* resource password                */
static char pAGETTOK_PASS [MAX_LINE];   /* printable password               */
static char cAGETTOK_PASS [MAX_LINE];   /* encrypted password               */

static char NAME_BUFFER [MAX_LINE];     /* unix:afs:resource name triple    */
static char LINE_BUFFER [MAX_LINE];     /* buffer for entries from file     */

static char DELETED []= "deleted";

/* ------------------------------------------------------------------------ */
int agettok_get_hash_key (
char *user_from,
char *user_to,
char *resource_name,
char *hash,
char *key,
int hash_size)
{
  int i;
  char *cp;
  unsigned char *digest;

  if (user_from == (char *) 0 || *user_from == 0
      || user_to == (char *) 0 || *user_to == 0
      || resource_name == (char *) 0 || *resource_name == 0
     )
    return -1;
     
  if (hash_size <= 0 || hash_size >= 32) return -1;

  sprintf (NAME_BUFFER, "%s:%s:%s", user_from, user_to, resource_name);
#ifdef DEBUG
printf ("hash base: '%s'\n", NAME_BUFFER);
#endif
  digest= MD5chk2_block ((unsigned char *) NAME_BUFFER, strlen (NAME_BUFFER));

  cp= (char *) digest;
  for (i= 0; i < AGETTOK_HASH_SIZE; i++) *hash++= *cp++;
  for (;     i < 16;                i++) *key++= *cp++;
  *hash= *key= 0;

  return 0;
}

/* ------------------------------------------------------------------------ */
char *agettok_get_resource_password (
char *file_name,
char *user_from,
char *user_to,
char *resource_name,
int get_flags)
{
  int rc;
  char *rv= (char *) 0;
  FILE *fi;
#define MAX_FIELDS 2
  char *fields [MAX_FIELDS];

  if (agettok_get_hash_key (user_from, user_to, resource_name,
                            AGETTOK_HASH, AGETTOK_KEY, AGETTOK_HASH_SIZE)
      != 0) return (char *) 0;

  bin_to_hex (AGETTOK_HASH, pAGETTOK_HASH, AGETTOK_HASH_SIZE);

#ifdef DEBUG
printf ("hash string: '%s'\n", pAGETTOK_HASH);
#endif

  if ((fi= fopen (file_name, "r")) == (FILE *) 0)
  {
#ifdef DEBUG
printf ("passwd_file not open: '%s'\n", file_name);
#endif
    return (char *) 0;
  }

  for (;;)
  {
    rc= fread_line (fi, LINE_BUFFER, MAX_LINE);
    if (rc <= 0 && feof (fi)) break;
    if (LINE_BUFFER [0] == '#') continue;

    rc= split_string (LINE_BUFFER, ':', fields, MAX_FIELDS);
    if (rc != 2) continue;
    if (strcmp (fields [0], pAGETTOK_HASH) == 0)
    {
      strcpy (pAGETTOK_PASS, fields [1]);
      rv= pAGETTOK_PASS;
      /* don't break the loop, the latest entry is valid */
    }
  }
  fclose (fi);

  if (rv != (char *) 0)
  {
    if (strcmp (pAGETTOK_PASS, DELETED) == 0) return (char *) 0;

    hex_to_bin (pAGETTOK_PASS, AGETTOK_PASS, strlen (pAGETTOK_PASS));

    if (!(get_flags & AGETTOK_clear_password))
      ggcrypt_block ((unsigned char *) AGETTOK_PASS,
                     strlen (pAGETTOK_PASS)/2,
                     (unsigned char *) AGETTOK_KEY,
                     16-AGETTOK_HASH_SIZE);

    rv= AGETTOK_PASS;
#ifdef DEBUG
printf ("password: %s\n", rv);
#endif
  }

  return rv;
}

/* ------------------------------------------------------------------------ */
char *agettok_get_resource_entry (
char *file_name,
char *user_from,
char *user_to,
char *resource_name)
{
  int rc;
  char *rv= (char *) 0;
  FILE *fi;
  int p_hash_size= AGETTOK_HASH_SIZE*2;

  if (agettok_get_hash_key (user_from, user_to, resource_name,
                            AGETTOK_HASH, AGETTOK_KEY, AGETTOK_HASH_SIZE)
      != 0) return (char *) 0;

  bin_to_hex (AGETTOK_HASH, pAGETTOK_HASH, AGETTOK_HASH_SIZE);

#ifdef DEBUG
printf ("hash string: '%s'\n", pAGETTOK_HASH);
#endif

  if ((fi= fopen (file_name, "r")) == (FILE *) 0) return (char *) 0;

  for (;;)
  {
    rc= fread_line (fi, LINE_BUFFER, MAX_LINE);
    if (rc <= 0 && feof (fi)) break;
    if (LINE_BUFFER [0] == '#') continue;

    if (strncmp (LINE_BUFFER, pAGETTOK_HASH, p_hash_size) == 0
        && LINE_BUFFER [p_hash_size] == ':'
       )
    {
      rv= LINE_BUFFER;
      /* don't break the loop, the latest entry is valid */
    }
  }
  fclose (fi);

  return (rv == (char *) 0) ? (char *) 0 : strdup (rv);
}

/* ------------------------------------------------------------------------ */
int agettok_set_resource_password (
char *file_name,
char *user_from,
char *user_to,
char *resource_name,
char *resource_password,
int set_flags)
{
  FILE *fo;
  int lng;

  if (resource_password == (char *) 0
      || *resource_password == 0
      || strlen (resource_password) <= 3
      || agettok_get_hash_key (user_from, user_to, resource_name,
                               AGETTOK_HASH, AGETTOK_KEY,
                               AGETTOK_HASH_SIZE) != 0
     )
    return -1;

  bin_to_hex (AGETTOK_HASH, pAGETTOK_HASH, AGETTOK_HASH_SIZE);

#ifdef DEBUG
printf ("hash string: '%s'\n", pAGETTOK_HASH);
#endif

  if (strcmp (resource_password, DELETED) == 0)
  {
    strcpy (pAGETTOK_PASS, resource_password);
  }
  else
  {
    lng= strlen (resource_password);
    strcpy (cAGETTOK_PASS, resource_password);
    if (!(set_flags & AGETTOK_clear_password))
      ggcrypt_block ((unsigned char *) cAGETTOK_PASS, lng,
                     (unsigned char *) AGETTOK_KEY, 16-AGETTOK_HASH_SIZE);

    bin_to_hex (cAGETTOK_PASS, pAGETTOK_PASS, lng);

#ifdef DEBUG
printf ("password string: '%s'\n", pAGETTOK_PASS);
#endif
  }

  if ((fo= fopen (file_name, "a")) == (FILE *) 0) return -1;

  fprintf (fo, "%s:%s\n", pAGETTOK_HASH, pAGETTOK_PASS);
  fclose (fo);

  if (set_flags & AGETTOK_write_entry)
    printf ("%s:%s\n", pAGETTOK_HASH, pAGETTOK_PASS);

  return 0;
}
