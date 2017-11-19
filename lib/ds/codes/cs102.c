/*
 *  File %dpp/codes/cs102.c
 *
 *  *** OBSOLOETE ***
 *
 *  entity translation
 *
 *  written:       1992-12-27: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/fileio.h>
#include <gg/filename.h>
#include <gg/lookup.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
static int module_uninitialized= 1;
static int auto_initialized= 0;
static char *lut= (char *) 0;
static long lut_size= 0L;

/* ------------------------------------------------------------------------ */
int INIT_find_sgml_entity (char *fnm_lut)
{
  if (!module_uninitialized)
  {
    free (lut);
    lut= (char *) 0;  /* a new buffer will be allocated     */
    lut_size= 0L;
  }

  if ((lut_size= read_file2buffer (&lut, fnm_lut, 32000L)) == -1L) return -1;

  module_uninitialized= 0;

  return 0;
}

/* ------------------------------------------------------------------------ */
int KILL_find_sgml_entity ()
{
  if (module_uninitialized) return 0;

  if (lut != (char *) 0) free (lut);
  lut= (char *) 0;
  lut_size= 0L;

  module_uninitialized= 1;

  return 0;
}

/* ------------------------------------------------------------------------ */
int find_sgml_entity (char *entity)
{
  int rc;
  long info;
  int lng;

  if (entity == (char *) 0 || *entity == 0) return -1;

  if (module_uninitialized)
  {
    rc= (auto_initialized)
        ? -1
        : INIT_find_sgml_entity (
            set_etc_filename ((char *) 0, CSF_PC_COMPACT_LUT));

    auto_initialized= 1;

    if (rc == -1)
    { /* default values if really nothing is available */
      if (strcmp (entity,  "lt") == 0) return 0x3C;
      if (strcmp (entity,  "gt") == 0) return 0x3E;
      if (strcmp (entity, "amp") == 0) return 0x26;
      return -1;
    }
  }

  if (lookup_char (lut, entity, &info, &lng) != LOOKUP_found) return -1;

  return (int) info;
}
