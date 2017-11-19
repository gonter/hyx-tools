/*
 *  FILE %ds/strings/str_0039.c
 *
 *  generate a random password with a given length
 *  based on mk_passwd ()
 *
 *  written:       1995-05-12
 *  latest update: 2000-08-21  0:53:19
 *  $Id: str_0039.c,v 1.3 2000/08/28 19:27:02 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <time.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/dpp.h>

#ifndef MSDOS
#include <sys/types.h>
#include <unistd.h>
#endif

/* ------------------------------------------------------------------------ */
static char *PASS_CHARS=
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

#define PASSWORD_ALPHABETH_SIZE 62

static int initialized= 0;

/* ------------------------------------------------------------------------ */
int mk_PassWord (char *s, int pass_lng)
{
  long r;
  int i;

  if (!initialized)
  {
    alt_seed ();
    initialized= 1;
  }

  for (i= 0; i < pass_lng; i++)
  {
    r= rand () % PASSWORD_ALPHABETH_SIZE;
    s [i]= PASS_CHARS [r];
  }

  s [i]= 0;

  return 0;
}
