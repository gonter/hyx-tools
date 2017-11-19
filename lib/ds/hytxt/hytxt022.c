/*
 *  FILE %ds/hytxt/hytxt022.c
 *
 *  written:       1994-07-10 extracted from %sgml/hytxt016.c
 *  latest update: 1996-03-24 17:42:25
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
long hyx_get_index (
FILE *fi_idx,
FILE *fi_lut,
FILE *fi_xfn,
char *frame_name)
{
  long idx= -1L;

  if (strcmp ("$$random", frame_name) == 0)
  {
    idx= hyx_get_random_index (fi_idx);
  }
  else
  if (frame_name [0] == '$' && frame_name [1] == '#')
  {
    idx= get_parameter_value (frame_name+2);
  }
  else
  {
    if (fi_lut != (FILE *) 0)
      idx= find_frame_lut (fi_lut, frame_name);

    if (idx == -1L && fi_xfn != (FILE *) 0)
      idx= find_frame_xfn (fi_xfn, frame_name);
  }

  return idx;
}
