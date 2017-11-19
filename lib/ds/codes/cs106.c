/*
 *  File %ds/codes/cs106.c
 *
 *  CS_ET8: entity translation functions
 *
 *  written:       1995-12-10: g.gonter@ieee.org
 *  latest update: 1995-12-29
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/fileio.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
int cs_et8_entity2code (struct CS_ET8 *et8, char *entity)
{
  long rc;
  char *lut;
  long info;
  int lng;
  
  if (et8 == (struct CS_ET8 *) 0
      || et8->CS_et8_error_flag != 0    /* table can't be used!             */
     )
  {
    if (entity == (char *) 0 || *entity == 0) return -1;
    if (strcmp (entity,  "lt") == 0) return 0x3C;
    if (strcmp (entity,  "gt") == 0) return 0x3E;
    if (strcmp (entity, "amp") == 0) return 0x26;
    return -1;
  }

  /* load lookup table now if its not already loaded */
  if ((lut= et8->CS_et8_lut) == (char *) 0)
  {
    rc= read_file2buffer ((char **) &et8->CS_et8_lut,
                          et8->CS_et8_lut_fnm, MAX_CS_ET8_SIZE);

#ifdef DEBUG
    fprintf (stderr, ">>> reading %s -> %ld diag=%d\n",
             et8->CS_et8_index_fnm, rc, gg_diagnose);
#endif

    if (rc == -1L)
    {
      et8->CS_et8_error_flag= 3;
      return -1;
    }
    lut= et8->CS_et8_lut;
  }

  if (lookup_char (lut, entity, &info, &lng) != LOOKUP_found) return -1;

  return (int) info;
}
