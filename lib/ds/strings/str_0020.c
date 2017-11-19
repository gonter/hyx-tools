/*
 *  FILE %ds/strings/str_0020.c
 *
 *  split a string into fields  
 *
 *  written:       1993-04-23
 *  latest update: 1996-02-25  0:29:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int split_string (char *src, int spl, char *flds[], int n_flds)
{
  int cnt= 0;           /* number of fields identified                      */
  int flg= 0;           /* 0 -> new field begins                            */
                        /* 1 -> within a field                              */

  if (src == (char *) 0 || *src == 0) return 0;

  for (; *src; src++)
  {
    if (flg == 0)
    {
      if (n_flds > 0)
      {
        flds [cnt]= src;
        n_flds--;
      }
      cnt++;
      flg= 1;
    }

    if (((int) (*src & 0x00FF)) == spl)
    {
      flg= 0;
      if (n_flds > 0) *src= 0;
    }
  }

  if (flg == 0)
  {
    if (n_flds > 0) flds [cnt]= src;
    cnt++;
  }

  return cnt;
}
