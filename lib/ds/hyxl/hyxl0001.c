/*
 *  FILE %ds/hyxl/hyxl0001.c
 *
 *  find an attribute name in a string
 *
 *  written:       1991 06 25: (original name: usr/ned/08/ned0837.c)
 *                 1993-03-07: renamed to usr/ds/hyx/hyxl0002.c
 *  latest update: 1997-06-16 10:55:34
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/hyx.h>

/* ------------------------------------------------------------------------ */
char *find_attr_name (char *str, char *name)
{
#define STAT_start     0
#define STAT_match     1
#define STAT_dquote    2
#define STAT_squote    3
#define STAT_nomatch   4
  int status= STAT_start;
  int ch;
  char *np;                     /* name pointer         */

  if (str == (char *) 0) return (char *) 0;

  np= name;

  for (; (ch= (*str & 0x00FF)) != 0; str++)
  {
    switch (status)
    {
      case STAT_start:
        if (ch == (*name & 0x00FF))
        {
          np= name;
          status= STAT_match;
        } else
        if (ch == '\"') status= STAT_dquote; else
        if (ch == '\'') status= STAT_squote; else
        if (ch != ' ' && ch != '\t') status= STAT_nomatch;
        break;

      case STAT_match:
        np++;
        if (ch == '=' && (*np & 0x00FF) == 0) return str+1;
        if (*np == 0) return (char *) 0;
        if (ch == (*np & 0x00FF)) break;
        status= STAT_nomatch;

      case STAT_nomatch:
        if (ch == ' ' || ch == '\t') status= STAT_start;
        if (ch == '\"') status= STAT_dquote; else
        if (ch == '\'') status= STAT_dquote;
        break;

      case STAT_dquote:
        if (ch == '\"') status= STAT_nomatch;
        break;
      case STAT_squote:
        if (ch == '\'') status= STAT_nomatch;
        break;
    }
  }

  return (char *) 0;
}
