/*
 *  FILE %ds/mail/mail0012.c
 *
 *  verify an email address
 *
 *  written:       1997-11-26
 *  latest update: 1997-11-27 12:39:52
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
int mail_verify_domain_name (
char *addr,
int dup,
struct MAIL_VERIFY_DB *db)
{
  int nsd;
  int i, rc, ch;
  int flg;
#define MAX_SD 10
  char *sd [MAX_SD];
  char *asd;
  DB_lookup *dbq;

  if (addr == (char *) 0 || *addr == 0
      || (dup && (addr= strdup (addr)) == (char *) 0)
     ) return -1;

  nsd= split_string (addr, '.', sd, MAX_SD);
  if (nsd >= MAX_SD || nsd <= 1)
  {
SYNTAX:
    rc= ADDR_SYNTAX;
    goto DONE;
  }

  if (!mail_valid_tld (sd [nsd-1]))
  {
    rc= ADDR_INVALID;
    goto DONE;
  }

  /* look at each segment of the domain name */
  for (i= nsd-2; i >= 0; i--)
  {
    asd= sd[i];
    if (*asd == 0) goto SYNTAX;

    flg= 0;
    while (ch= *asd++ & 0x00FF)
    {
      if (ch >= '0' && ch <= '9') flg |= 0x01;
      else if (ch >= 'a' && ch <= 'z') flg |= 0x02;
      else if (ch >= 'A' && ch <= 'Z') flg |= 0x02;
      else if (ch == '-') flg |= 0x04;
      else goto SYNTAX; /* any other char is not allowed */
    }

    if (!(flg & 0x02)) goto SYNTAX;  /* numeric only domain not allowed */

    /* domain name segment is ok, re-join it with the following semgent */
    sd[i+1][-1]= '.';

    /* T2D: lookup domain in spammer database and return error */
    if ((dbq= db->spamsites) != (DB_lookup *) 0
        && (*dbq) (addr, db->cd_spamsites) > 0
       )
    {
      rc= ADDR_SPAMSITE;
      goto DONE;
    }
  }

  rc= 0;
DONE:
  if (dup) free (addr);
  return rc;
}
