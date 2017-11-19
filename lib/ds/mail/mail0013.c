/*
 *  FILE %ds/mail/mail0013.c
 *
 *  verify the correctness of a toplevel domain
 *
 *  written:       1997-11-26
 *  latest update: 1997-11-26 13:07:29
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
#define N_TLD 14
static char *TLD [N_TLD] =   /* registered top level domains */
{
  "com", "edu", "gov", "mil", "net", "org", "int", 

  "firm", "store", "web", "arts", "rec", "info", "nom"  /* not yet ... */
} ;

/* ------------------------------------------------------------------------ */
#define N_vTLD 3
static char *vTLD [N_vTLD] =  /* virtual top level domains */
{
  "bitnet", "arpa", "uucp"
} ;

/* ------------------------------------------------------------------------ */
int mail_valid_tld (char *tld)
{
  int ch;

  if (find_command (tld, TLD, 0, N_TLD) >= 0
      || (strlen (tld) == 2
          && ((ch= tld [0]) >= 'a' && ch <= 'z'
              && (ch= tld [1]) >= 'a' && ch <= 'z')
         ) /* country code */
      || find_command (tld, vTLD, 0, N_vTLD) >= 0
     ) return 1;

  return 0;
}
