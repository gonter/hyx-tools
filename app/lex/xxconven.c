/*
 *  FILE /usr/lex/xxconven.c
 *
 *  1992 02 19
 *
 */

#include <string.h>

/* ------------------------------------------------------------------------ */
int xxconvent (char *lps, char *lpd)
{
  int id=0;
  int is=0;

  for (is=0; lps[is]; is++)
  {
    if ((lps[is] & 0x00FF) == 0x0D) continue;
    if ((lps[is] & 0x00FF) == 0x0A) continue;
    if ((lps[is] & 0x00FF) == 0x09) lps[is] = (char) 0x20;
    if ((lps[is] & 0x00FF) >= 0x7F) return -1;
    if ((lps[is] & 0x00FF) <  0x20) return -1;
    if (is==0) goto DEF;

    switch (lps[is])
    {
      case '\"':
        switch (lps [is-1])
        {
          case 'a': strcpy (&lpd[id-1], "&auml;"); break;
          case 'o': strcpy (&lpd[id-1], "&ouml;"); break;
          case 'u': strcpy (&lpd[id-1], "&uuml;"); break;
          case 'A': strcpy (&lpd[id-1], "&Auml;"); break;
          case 'O': strcpy (&lpd[id-1], "&Ouml;"); break;
          case 'U': strcpy (&lpd[id-1], "&Uuml;"); break;
          default: return -1;
        }
        id = strlen (lpd);
        break;
      case 'S':
        if (lps [is-1] != 's') goto DEF;
        strcpy (&lpd[id-1], "&szlig;");
        id = strlen (lpd);
        break;
      default:
DEF:
        lpd[id++] = lps[is];
        lpd[id]=0;
        break;
    }
  }

  return id;
}
