/*
 *  File %dpp/codes/cs103.c
 *
 *  CS_ET8: entity translation functions
 *
 *  written:       1995-12-10: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
struct CS_ET8 *cs_et8_create_table (
long table_id,
char *fnm_dat,
char *fnm_idx,
char *fnm_lut)
{
  struct CS_ET8 *et8;

  if (fnm_dat == (char *) 0
      || *fnm_dat == 0
      || (et8= ((struct CS_ET8 *) calloc (sizeof (struct CS_ET8), 1)))
         == (struct CS_ET8 *) 0
      || (et8->CS_et8_string_fnm= strdup (fnm_dat)) == (char *) 0
      || (et8->CS_et8_index_fnm= fnmcpy4 (fnm_idx, fnm_dat, ".idx"))
         == (char *) 0
      || (et8->CS_et8_lut_fnm= fnmcpy4 (fnm_lut, fnm_dat, ".lut"))
         == (char *) 0
     ) return (struct CS_ET8 *) 0;

  et8->CS_et8_table_id= table_id;
  
  return et8;
}
