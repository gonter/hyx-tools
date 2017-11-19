/*
 *  FILE %ds/ggcrypt/ggcryp18.c
 *
 *  written:       1996-08-11
 *  latest update: 1996-08-11 18:53:59
 *
 */

#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/ggcrypt.h>

/* ------------------------------------------------------------------------ */
int ggc_dispose_block (char **cpp, int lng)
{
  char *cp;

  if (cpp == (char **) 0) return -1;

  if ((cp= *cpp) != (char *) 0)
  {
    if (lng <= 0) lng= strlen (cp);
    mk_PassWord (cp, lng);
    free (cp);
    *cpp= (char *) 0;
  }

  return 0;
}
