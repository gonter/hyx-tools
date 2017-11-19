/*
 *  FILE %ds/strings/str_0201.c
 *
 *  return 1 if one string is the abbreviation of the other one
 *  return 0 if it's not a abbreviation
 *  return -1 in case of an error
 *
 *  written:       1992 03 13
 *  latest update: 1995-12-13
 *  $Id: str_0201.c,v 1.2 2005/09/04 20:27:37 gonter Exp $
 *
 */

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int abbrev (const char *unabbr, const char *abbr, int lng)
{
  int i;
  int c;

/*  printf ("unabbr=%s, abbr=%s, i=%d\n", unabbr, abbr, i); */
  if (unabbr == (char *) 0 || abbr == (char *) 0) return -1; /* or 0 ? */

  for (i= 0; ((int) *abbr) == (c= ((int) *unabbr)) && c; i++)
  {
    abbr++;
    unabbr++;
  }

/*  printf ("unabbr=%s, abbr=%s, i=%d\n", unabbr, abbr, i); */

  if (*abbr == 0 && i >= lng) return 1;
  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef _DEBUG_MODULE_
t_abbrev (char *s1, char *s2, int l)
{
  printf ("abbrev(\"%s\",\"%s\",%d) -> %d\n",
    s1, s2, l,
    abbrev (s1, s2, l));
}

main ()
{
  t_abbrev ("Gerhard", "Ger", 0);
  t_abbrev ("Gerhard", "Ger", 2);
  t_abbrev ("Gerhard", "Ger", 3);
  t_abbrev ("Gerhard", "Ger", 4);
  t_abbrev ("Gerhard", "ger", 0);
  t_abbrev ("Gerhard", "Gerald", 3);
  t_abbrev ("Gerhard", "Gerhard", 3);
}
#endif
