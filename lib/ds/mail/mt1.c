/*
 *  FILE %ds/mail/mt1.c
 *
 *  test address check function
 *
 *  written:       1997-11-26
 *  latest update: 1997-11-26 13:07:29
 *
 */

#include <stdio.h>
#include <gg/strings.h>
#include <gg/rfc822.h>

#ifdef MT1
#define CHECK(s,f,db) mail_verify_address(s,f,db)
#endif

#ifdef MT2
#define CHECK(s,f,db) mail_verify_message_id(s,f,1,db)
#endif

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, rc;
  char *arg;
  int done= 0;
  struct MAIL_VERIFY_DB *db= (struct MAIL_VERIFY_DB *) 0;

  for (i= 1; i < argc; i++)
  {
    arg= argv[i];

    rc= CHECK (arg, 1, db);
    printf ("CHECK %d <- '%s'\n", rc, arg);
    done++;
  }

  if (!done)
  {
    char line [128];

    for (;;)
    {
      scanf ("%s", line);

      rc= CHECK (line, 1, db);
      printf ("CHECK %d <- '%s'\n", rc, line);
    }
  }

  return 0;
}
