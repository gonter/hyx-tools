/*
 *  FILE %ds/strings/str_0016.c
 *
 *  identify a command in a line of text.
 *
 *  written:       1992-12-08
 *  latest update: 1996-09-22 13:47:19
 *  $Id: str_0016.c,v 1.2 2004/05/25 22:07:18 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int find_command (char *s, char *cmds[], int first, int last)
{
  int i;
  int cl;
  char *c;
  int ch;

  if (s == (char *) 0) return -1;

  for (; (ch= *s) && (ch == ' ' || ch == '\t'); s++);
  if (*s == 0) return -1;

  for (i= first; i <= last; i++)
  {
    if ((c= cmds[i]) == (char *) 0) continue;

    cl= strlen (c);
    if (strncmp (s, c, cl) == 0
       && (s [cl] == 0 || s [cl] == ' ' || s [cl] == '\t')) return i;
  }

  return -1;
}
