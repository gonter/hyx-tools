/*
 *  FILE ~/usr/sgml/msrv05.c
 *
 *  written:       1994-07-03
 *  latest update: 1999-04-24 12:00:49
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include "msrvh.h"

/* ------------------------------------------------------------------------ */
struct MSRV_authorization *msrv_make_authorization (char *user, char *key)
{
  struct MSRV_authorization *msrv_auth;

  if ((msrv_auth= (struct MSRV_authorization *)
                  calloc (sizeof (struct MSRV_authorization), 1))
      != (struct MSRV_authorization *) 0)
  {
    msrv_auth->MA_user= strdup (user);
    msrv_auth->MA_key= strdup (key);
  }

  return msrv_auth;
}
