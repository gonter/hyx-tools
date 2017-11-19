/*
 *  FILE %ds/hyxl/hyxl0002.c
 *
 *  return the value of an attribute assignment
 *
 *  written:       1991 05 23: (original name: usr/ned/08/ned0837.c)
 *                 1993-03-07: renamed to usr/ds/hyx/hyxl0002.c
 *  latest update: 1997-12-18 12:54:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/hyx.h>

/* ------------------------------------------------------------------------ */
int get_attr_value (char *src, char *dst, int dst_lng, int flags)
/* flags: bit 0: 1 -> remove quotes */
{
  int j= 0;                     /* desintation index                        */
  int c;                        /* examined character                       */
  int i;                        /* examined character index                 */
  int quoted= 0;                /* 1 -> string is quoted                    */
  int store= 1;                 /* 1 -> examined character to be stored     */

  if (src == (char *) 0 || dst == (char *) 0 || dst_lng <= 0) return -1;
  dst [0]= 0;

  for (i= 0;; i++)
  {
    c= src [i];
    if (c == 0) break;

    if (c == '\"' || c == '\'')
    {
      if (flags & 0x01)
      {
        if (i == 0)
        {
          quoted= c;
          store= 0;
        }
        else
        if (quoted == c)
        {
          break;                /* end of strimg! */
        }
      }
    }
    else
      if (quoted == 0
          && (c == ' ' || c == '\t'
             || c == '\r' || c == '\n'
             || c == '>')) break;

    if (store)
    {
      dst [j++]= (char) c;
      if (j >= dst_lng)
      {
        dst [j-1]= 0;
        return -1;
      }
    }
    store= 1;
  }

  dst [j]= 0;
  return 0;
}
