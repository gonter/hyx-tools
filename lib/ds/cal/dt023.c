/*
 *  FILE %ds/cal/dt023.c
 *
 *  operations with date and time
 *
 *  written:       1988 03 28: (as datum.c)
 *                 1991 06 24: revision
 *                 1994-05-07: revision: split up in more modules
 *  latest update: 1996-11-10 15:05:54
 *
 */

#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int get_jahr_mon_tag (
char *s,        /* I:   Datumsstring    */
int *ii,        /* I/O: Scanner Index   */
int *vv,        /* O:   Jahr / Monat / Tag als Integer */
char *m,        /* O:   Monat als String*/
int ms,         /* I:   ???     */
int *msr)       /* O:   ???     */
{
  int i;
  int v= 0;     /* numberic value of some items */
  int mi= 0;
  int c;

  i= *ii;

  while ((c= s [i])    == ' ' || c == ':' || c == '_' ||
         c == '-' || c == '+' || c == '=' || c == '|' ||
         c == ',' || c == '.' || c == ';' || c == '/') i++;

  if ((c= s [i]) >= '0' && c <= '9')
  {
    for (; c = s [i]; i++)
      if (c >= '0' && c <= '9')
        v= v*10+ s [i] - '0';
      else break;
  }
  else
  {
    for (; c = s [i]; i++)
      if (c >= 'a' && c <= 'z')
      {
        m [mi++]= (char) c;
        m [mi]= 0;
        *msr= ms;
      }
      else break;
  }

  *ii= i;
  *vv= v;

  return 0;
}
