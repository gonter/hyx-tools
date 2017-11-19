/*
 *  FILE %ds/mail/mail0011.c
 *
 *  verify an email address
 *
 *  written:       1997-11-26
 *  latest update: 1997-11-27 12:45:50
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
int mail_verify_address (
char *addr,
int dup,
struct MAIL_VERIFY_DB *db)
{
  int rc= 0;
  char *user, *domain, *f[2];
  int nf;
  int ch, i;
  int lng_user, lng_domain;
  DB_lookup *dbq;

  if (addr == (char *) 0
      || (dup && (addr= strdup (addr)) == (char *) 0)
     ) return -1;

  to_lower (addr);

  /* lookup address in goodaddr database, return ok if found */
  if ((dbq= db->goodaddr) != (DB_lookup *) 0
      && (*dbq) (addr, db->cd_goodaddr) > 0
     )
  {
    rc= 0;
    goto DONE;
  }

  /* lookup address in spammer database, return spammer if found */
  if ((dbq= db->spammers) != (DB_lookup *) 0
      && (*dbq) (addr, db->cd_spammers) > 0
     )
  {
    rc= ADDR_SPAMMER;
    goto DONE;
  }

  nf= split_string (addr, '@', f, 2);
  if (nf != 2
      || (lng_user= strlen (user= f[0])) <= 0
      || (lng_domain= strlen (domain= f[1])) <= 0
     )
  {
    rc= ADDR_SYNTAX;
    goto DONE;
  }

  /* certain well known domains have their special naming rules */
  if (strcmp (domain, "aol.com") == 0)
  {
    if (lng_user < 3
        || lng_user > 20   /* as of 1997-11-26: max 10 chars, to be changed */
       )
    {
FAKED:
      rc= ADDR_INVALID;
      goto DONE;
    }

    for (i= 0; ch= user [i] & 0x00FF; i++)
    {
      if (!((ch >= 'a' && ch <= 'z')
            || (ch >= 'A' && ch <= 'Z')
            || (ch >= '0' && ch <= '9' && i > 0)
            || (ch == '+' && i > 0)
           )
         ) goto FAKED;
    }
  }
  else
  {
    rc= mail_verify_domain_name (domain, 0, db);
    if (rc != 0) goto DONE;
  }

  rc= 0;

DONE:
  if (dup) free (addr);
  return rc;
}
