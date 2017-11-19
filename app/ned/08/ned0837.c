/*
 *  FILE ~/usr/ned/08/ned0837.c
 *
 *  ***** NOT USED, moved to library !!!!
 *
 *  written:       1991 05 23
 *  latest update: 1994-12-28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int get_attr_value (char *src, char *dst, int dst_lng, int flags)
/* flags: bit 0: 1 -> remove quotes */
{
  int i=0, j=0, c;
  int quoted=0;
  int store=1;

  if (src == (char *) 0 || dst == (char *) 0 || dst_lng <= 0) return -1;
  dst[0]=0;

  for (i=0;; i++)
  {
    c=src[i];
    if (c == 0) break;
    if (c == '\"')
    {
      quoted= (quoted) ? 0 : 1;
      if (flags & 0x01) store=0;
    } else
    if (quoted == 0
        && (c == 0x20 || c == 0x09 || c == 0x0D || c == 0x0A)) break;
    if (store)
    {
      dst[j++] = (char) c;
      if (j >= dst_lng)
      {
        dst[j-1]=0;
        return -1;
      }
    }
    store=1;
  }

  dst[j]=0;
  return 0;
}
