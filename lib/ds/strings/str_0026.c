/*
 *  FILE %ds/strings/str_0026.c
 *
 *  isolate words out of a string.
 *
 *  written:       1993-12-10 copied from str_0022.c
 *  latest update: 1995-12-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <ctype.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int isolate2words (char *src, char *flds[], int n_flds, int *table)
{
  int ch;                       /* character unter observation              */
  int cnt= 0;                   /* number of words isolated                 */
#define STA_noword      0       /* no word has been identified              */
#define STA_word        1       /* word has been identified                 */
  int sta= STA_noword;          /* status of the isolator automaton         */

  if (table == (int *) 0) return -1;
  if (src == (char *) 0) return 0;

  for (; (ch= *src & 0x00FF) != 0; src++)
  {
    switch (sta)
    {
      case STA_noword:
        if (table [ch])
        {
          if (n_flds > 0)
          {
            flds [cnt]= src;
            n_flds--;
          }
          cnt++;
          sta= STA_word;
        }
        break;

      case STA_word:
        if (!table [ch])
        {
          if (n_flds > 0) *src= 0;
          sta= STA_noword;
        }
        break;
    }
  }

  return cnt;
}
