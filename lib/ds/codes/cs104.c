/*
 *  File %dpp/codes/cs104.c
 *
 *  CS_ET8: entity translation functions
 *
 *  written:       1995-12-10: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdlib.h>
#include <gg/strings.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
int cs_et8_destroy_table (struct CS_ET8 *et8)
{
  if (et8 == (struct CS_ET8 *) 0) return -1;

  /* get rid of the lookup table */
  free_or_what (et8->CS_et8_lut_fnm);
  free_or_what (et8->CS_et8_lut);

  /* get rid of the index table */
  free_or_what (et8->CS_et8_index_fnm);
  free_or_what (et8->CS_et8_index);

  /* get rid of the string buffer */
  free_or_what (et8->CS_et8_string_fnm);
  free_or_what (et8->CS_et8_string_buffer);

  free (et8);

  return 0;
}
