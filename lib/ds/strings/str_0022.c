/*
 *  FILE ~/usr/sbr/str_0022.c
 *
 *  isolate words out of a string.
 *
 *  written:       1993-04-23
 *  latest update: 1998-02-18 17:03:41
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <ctype.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int isolate_words (char *src, char *flds[], int n_flds)
{
  int ch;                       /* character unter observation              */
  int cnt= 0;                   /* number of words isolated                 */
#define STA_noword      0       /* no word has been identified              */
#define STA_word        1       /* word has been identified                 */
  int sta= STA_noword;          /* status of the isolator automaton         */

  if (src == (char *) 0) return 0;

  for (; (ch= *src & 0x00FF) != 0; src++)
  {
    switch (sta)
    {
      case STA_noword:
        if (isalpha(ch) || isdigit(ch) || ch=='_' || ch=='*' || ch=='$')
        {
          if (n_flds>0)
          {
            flds[cnt]= src;
            n_flds--;
          }
          cnt++;
          sta= STA_word;
        }
        break;

      case STA_word:
        if (!(isalpha(ch) || isdigit(ch) || ch=='_' || ch=='*' || ch=='$'))
        {
          if (n_flds>0) *src= 0;
          sta= STA_noword;
        }
        break;
    }
  }

  return cnt;
}
