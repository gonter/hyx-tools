/*
 *  FILE ~/usr/ds/hyxl/hyxl0003.c
 *
 *  find and return the value of an attribute assignment
 *
 *  written:       1991 05 23: (original name: ~/usr/ned/08/ned0837.c)
 *                 1993-03-07: renamed to ~/usr/ds/hyx/hyxl0002.c
 *  latest update: 1995-05-21
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/hyx.h>

/* ------------------------------------------------------------------------ */
int find_attr_value (char *src, char *dst, int dst_size, char *name)
{
  char *idx;

  if ((idx= find_attr_name (src, name)) != (char *) 0)
    if (get_attr_value (idx, dst, dst_size, 0x01) == 0) return 0;

  return -1;
}
