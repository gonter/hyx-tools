/*
 *  FILE %ds/strings/str_0043.c
 *
 *  generate a random password with a given length
 *  based on mk_passwd ()
 *
 *  written:       1995-10-04
 *  latest update: 1995-11-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <time.h>
#include <stdlib.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
static char *PASS_CHARS=
  "0123456789";

#define PASSWORD_ALPHABETH_SIZE 10

static int initialized= 0;

/* ------------------------------------------------------------------------ */
int mk_pin_code (char *s, int pass_lng)
{
  long r;
  int i;

  if (!initialized)
  {
    srand ((unsigned int) time ((time_t *) 0));
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

/* ------------------------------------------------------------------------ */
#ifdef TEST
int main (int argc, char *argv [])
{
  int i;
  char pin [10];
  for (i= 0; i<300; i++)
  {
    mk_pin_code (pin, 4);
    printf ("%s\n", pin);
  }
  return 0;
}
#endif
