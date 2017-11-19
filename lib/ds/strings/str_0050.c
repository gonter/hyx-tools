/*
 *  FILE %ds/strings/str_0050.c
 *
 *  written:       1997-06-11
 *  latest update: 1997-06-11 11:08:12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

static char *ES= "";

/* ------------------------------------------------------------------------ */
int strcmp_nn (char *s1, char *s2)
{
#ifdef __V1__
  if (s1 == (char *) 0 && s2 == (char *) 0) return 0;
  if (s1 == (char *) 0) return -1;
  if (s2 == (char *) 0) return 1;
#endif /* __V1__ */

  if (s1 == (char *) 0) s1= ES;
  if (s2 == (char *) 0) s2= ES;

  return strcmp (s1, s2);
}
