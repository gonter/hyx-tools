/*
 *  FILE %ds/mail/mail0014.c
 *
 *  verify a message id
 *
 *  written:       1997-11-27
 *  latest update: 1997-11-28 10:54:57
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
int mail_verify_message_id (
char *msgid,
int dup,
int defocus,                    /* strip off the angle brackets */
struct MAIL_VERIFY_DB *db)
{
  int rc= ADDR_SYNTAX;
  char *local, *domain, *f[2];
  int nf;
  int i;
  int lng_local, lng_domain;

  if (msgid == (char *) 0
      || (dup && (msgid= strdup (msgid)) == (char *) 0)
     ) return -1;

  /* message ids must have exactly one pair of angel brackets */
  if (defocus)
  {
    if (*msgid++ != '<'
        || (i= strlen (msgid)-1) < 1
        || msgid[i] != '>'
       )
      goto DONE;

    msgid [i]= 0;
  }


  to_lower (msgid);
  nf= split_string (msgid, '@', f, 2);

  if (nf != 2
      || (lng_local= strlen (local= f[0])) <= 0
      || (lng_domain= strlen (domain= f[1])) <= 0
     )
    goto DONE;

  /* domain part must be valid! */
  rc= mail_verify_domain_name (domain, 0, db);
  if (rc != 0) goto DONE;

  /* we are very rigid about the looks of the local part ;) */
  if (verify (local, "abcdefghijklmnopqrstuvwxyz0123456789-+./_=$"))
  {
    rc= ADDR_SYNTAX;
    goto DONE;
  }

DONE:
  if (dup) free (msgid);
  return rc;
}
